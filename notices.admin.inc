<?php

function notices_admin_settings(&$form_state) {
  $form = array();
  return system_settings_form($form);
}

function notices_settings_add(&$form_state) {
  $form = array();
  $form['uid'] = array(
    '#type'               => 'textfield',
    '#title'              => t('UID'),
    '#size'               => 50,
    '#maxlength'          => 255,
  );
  
  $form['callback'] = array(
    '#type'               => 'textfield',
    '#title'              => t('callback'),
    '#size'               => 50,
    '#maxlength'          => 255,
  );

  $form['message'] = array(
    '#type'               => 'textarea',
    '#title'              => t('Notice'),
    '#rows'               => 6,
    '#resizable'          => TRUE,
  );
  $format = FILTER_FORMAT_DEFAULT;
  if (isset($form_state['values']) && array_key_exists('format', $form_state['values'])) {
    $format = $form_state['values']['format'];
  }
  $form['format'] = filter_form($format);

  $form['#submit'][] = 'notices_settings_add_submit';
  return system_settings_form($form);
}

function notices_settings_add_submit($form, &$form_state) {
   $notice=$form_state['values'];
   notices_save($notice);
}

