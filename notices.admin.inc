<?php
/**
 * @file
 * Admin page settings module.
 */

/**
 * Menu callback to list sub-items.
 */
function notices_admin_menu_block_page() {
  $item = menu_get_item();
  module_load_include('inc', 'system', 'system.admin');

  if ($content = system_admin_menu_block($item)) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }

  return $output;
}

function notices_admin_settings($form, &$form_state) {
  $form['notices_lines_show_in_teaser'] = array(
    '#type' => 'select',
    '#title' => t('How many lines show in teaser'),
    '#options' => array(
      5 => 5,
      10 => 10,
      15 => 15,
    ),
    '#default_value' => variable_get('notices_lines_show_in_teaser', 5),
  );

  return system_settings_form($form);
}

function notices_settings_add($form, &$form_state) {
  $user_roles = array(
    0 => t('- Select -'),
  );

  $user_roles = array_merge($user_roles, user_roles(TRUE));

  $form['uid'] = array(
    '#type' => 'textfield',
    '#title' => t('UID'),
    '#size' => 50,
    '#maxlength' => 255,
  );

  $form['user_role'] = array(
    '#type' => 'select',
    '#title' => t('User roles'),
    '#options' => $user_roles,
    '#default_value' => 0,
  );

  $default_provider = FALSE;

  if (module_exists('notices_node')) {
    $default_provider = 'notices_node';
  }

  $form['provider'] = array(
    '#type' => 'textfield',
    '#title' => t('Provider'),
    '#size' => 50,
    '#maxlength' => 255,
    '#default_value' => $default_provider,
  );

  $form['message'] = array(
    '#type' => 'text_format',
    '#title' => t('Notice'),
    '#rows' => 6,
    '#resizable' => TRUE,
    '#format' => NULL,
  );

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );

  return $form;
}

/**
 * Implements hook_FORMID_validate().
 */
function notices_settings_add_validate($form, &$form_state) {
  $values = $form_state['values'];

  if ($values['user_role'] == 0) {
    $uid = $values['uid'];

    $user = db_select('users', 'u')
      ->condition('uid', $uid, '=')
      ->countQuery()
      ->execute()
      ->fetchField();

    if ($user == 0) {
      form_error($form['uid'], t('User not found.'));
    }
  }
  else {
    if (!user_role_load($values['user_role'])) {
      form_error($form['user_role'], t('Selected user role not found.'));
    }
  }
}

/**
 * Implements hook_FORMID_submit().
 */
function notices_settings_add_submit($form, &$form_state) {
  $values = $form_state['values'];

  $notice = new stdClass();
  $notice->provider = $values['provider'];
  $notice->message = $values['message']['value'];
  $notice->format = $values['message']['format'];

  if ($values['user_role'] == 0) {
    $notice->uid = $values['uid'];

    if (notices_save($notice)) {
      drupal_set_message(t('Notification has been sent!'));
    }
  }
  else {
    $role = user_role_load($values['user_role']);

    if ($role) {
      // All users on site.
      if ($values['user_role'] == 1) {
        $users = db_select('users', 'u')
          ->fields('u', array('uid'))
          ->condition('uid', 0, '!=')
          ->execute()
          ->fetchAll();
      }
      else {
        // Send notice to all users who role is $values['role_name'].
        $users = db_select('users_roles', 'r')
          ->fields('r', array('uid'))
          ->condition('rid', $role->rid)
          ->execute()
          ->fetchAll();
      }

      if (!empty($users)) {
        $success_count_send = 0;

        foreach ($users as $user) {
          $notice->uid = $user->uid;

          if (notices_save($notice)) {
            $success_count_send++;
          }
        }

        drupal_set_message(t('Notification has been success sent to @count users.', array(
          '@count' => $success_count_send,
        )));
      }
    }
  }
}
