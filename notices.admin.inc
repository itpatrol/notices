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
  $form = array();
  return system_settings_form($form);
}

function notices_settings_add($form, &$form_state) {
  $form = array();
  $form['uid'] = array(
    '#type'               => 'textfield',
    '#title'              => t('UID'),
    '#size'               => 50,
    '#maxlength'          => 255,
    '#required' => TRUE,
  );

  $form['provider'] = array(
    '#type'               => 'textfield',
    '#title'              => t('provider'),
    '#size'               => 50,
    '#maxlength'          => 255,
  );

  $form['message'] = array(
    '#type'               => 'text_format',
    '#title'              => t('Notice'),
    '#rows'               => 6,
    '#resizable'          => TRUE,
    '#format' => NULL,
  );

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update status of payment gateways'),
  );

  return $form;
}

/**
 * Implements hook_FORMID_validate().
 */
function notices_settings_add_validate($form, &$form_state) {
  $uid = $form_state['values']['uid'];

  $user = db_select('users', 'u')
    ->condition('uid', $uid, '=')
    ->countQuery()
    ->execute()
    ->fetchField();

  if ($user == 0) {
    form_error($form['uid'], t('User not found.'));
  }
}

/**
 * Implements hook_FORMID_submit().
 */
function notices_settings_add_submit($form, &$form_state) {
  $notice = new stdClass();
  $notice->uid = $form_state['values']['uid'];
  $notice->provider = $form_state['values']['provider'];
  $notice->message = $form_state['values']['message']['value'];
  $notice->format = $form_state['values']['message']['format'];

  if (notices_save($notice)) {
    drupal_set_message(t('Notification has been sent!'));
  }
}
