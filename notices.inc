<?php

function notices_list($account = NULL) {
  drupal_add_js(drupal_get_path('module', 'notices') . '/notices.js');
  drupal_add_css(drupal_get_path('module', 'notices') . '/notices.css');

  if (!is_object($account)) {
    global $user;

    $account = $user;
  }

  $notices = db_select('notices', 'n')
    ->extend('AltPager')
    ->extend('FormFilterAPI')
    ->fields('n')
    ->condition('uid', $account->uid)
    ->processFilters(NOTICES_FORM_NAME)
    ->orderBy('timestamp', 'DESC')
    ->execute()
    ->fetchAll();

  $output_notices = '';
  foreach ($notices as $notice) {
    $output_notices .= theme('notices_view_teaser', array('notice' => $notice));
  }

  if (empty($output_notices)) {
    $output_notices = t('No notifications.');
  }

  $pager_count_show = theme('altpager');

  $links = array(
    'links' => array(
      array(
        'href' => 'notices/mark-as-read',
        'title' => t('Mark as Read'),
        'attributes' => array('id' => 'notices-mark-as-read'),
      ),
      array(
        'href' => 'notices/settings',
        'title' => t('Settings'),
      ),
    ),
    'attributes' => array(
      'class' => 'notices-links',
    ),
  );

  $form = formfilterapi_get_form(NOTICES_FORM_NAME);

  $output = drupal_render($form);
  $output .= theme('links', $links);
  $output .= $pager_count_show;
  $output .= '<div id="notices" >';
  $output .= $output_notices;
  $output .= '</div>';
  $output .= $pager_count_show;

  return $output;
}


function notices_view($notice) {
  drupal_add_css(drupal_get_path('module', 'notices') . '/notices.css');

  $output = '<div id="notices">';
  $output .= theme('notices_view', array('notice' => $notice));
  $output .= '</div>';

  if ($notice->new) {
    notices_mark_read($notice);
  }

  return $output;
}

function notices_delete_form($form, &$form_state, $notice) {
  $form['noticeid'] = array(
    '#type' => 'value',
    '#value' => $notice->noticeid,
  );
  $form['alert'] = array(
    '#markup' => t('Do you want to delete this message?'),
  );
  $form['message'] = array(
    '#markup' => check_markup($notice->message, $notice->format, FALSE),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );
  return $form;
}

function notices_delete_form_submit($form, &$form_state) {
  notices_delete($form_state['values']['noticeid']);
  drupal_goto('notices');
}

function notices_settings($form, &$form_state) {
  global $user;

  $settings = notices_load_settings($user->uid);

  $send_options = array();
  $send_options_settings = array();
  foreach (module_implements('sendNotice') as $name) {
    $function = $name . '_sendNotice';
    $op = 'settings';
    $result = $function($op);
    $send_options[$name] = $result['title'];
    $send_options_settings[$name] = $result;
  }

  $provide_options = array();
  foreach (module_implements('provideNotice') as $name) {
    $function = $name . '_provideNotice';
    $op = 'settings';
    $result = $function($op);
    $provide_options[$name] = $result;
  }

  $form['providers'] = array(
    '#tree' => TRUE,
  );

  foreach ($provide_options as $provider) {
    $form['providers'][$provider['name']] = array(
      '#type' => 'fieldset',
      '#title' => $provider['title'],
      '#tree' => TRUE,
    );
    foreach ($send_options as $name => $title) {
      $form['providers'][$provider['name']][$name] = array(
        '#type' => 'fieldset',
        '#title' => $title,
        '#tree' => TRUE,
      );
      $form['providers'][$provider['name']][$name]['active'] = array(
        '#type'  => 'checkbox',
        '#title' => t('Activate'),
        '#default_value' => $settings->settings[$provider['name']][$name]['active'],
      );
      $form['providers'][$provider['name']][$name]['values'] = $send_options_settings[$name]['values'];
      foreach ($send_options_settings[$name]['values'] as $send_name => $value) {
        if (!empty($settings->settings[$provider['name']][$name]['values'][$send_name])) {
          $form['providers'][$provider['name']][$name]['values'][$send_name]['#default_value'] = $settings->settings[$provider['name']][$name]['values'][$send_name];
        }
      }
    }
  }

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save changes'),
  );

  return $form;
}

function notices_settings_submit($form, &$form_state) {
  global $user;

  $settings = notices_load_settings($user->uid);

  $settings->settings = serialize($form_state['values']['providers']);

  if ($settings->is_empty) {
    drupal_write_record('notices_settings', $settings);
  }
  else {
    drupal_write_record('notices_settings', $settings, 'uid');
  }

  drupal_set_message(t('Changes saved'));
}

function notices_mark_as_read() {
  global $user;

  db_update('notices')
    ->fields(array(
      'new' => 0,
    ))
    ->condition('uid', $user->uid, '=')
    ->execute();

  drupal_goto('notices');
}
