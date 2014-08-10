<?php
/**
 * @file
 * Admin page settings module.
 */

/**
 * Settings form.
 */
function notices_email_admin_settings() {
  $form['notices_email_debug'] = array(
    '#title' => t('Debug'),
    '#type' => 'select',
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#description' => t("Debug mode, don't send email, write to watchdog instead"),
    '#default_value' => variable_get('notices_email_debug', ''),
  );
  $form['notices_email_cron'] = array(
    '#title' => t('Cron'),
    '#type' => 'select',
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#description' => t('Select yes to process queue by cron'),
    '#default_value' => variable_get('notices_email_cron', ''),
  );
  $form['notices_email_letters_by_cron'] = array(
    '#title' => t('Amount of letter send by one cron run'),
    '#type' => 'textfield',
    '#default_value' => variable_get('notices_email_letters_by_cron', 20),
    '#size' => 5,
  );

  $form['notices_email_clean_spool_by_cron'] = array(
    '#title' => t('Periodicity of cleaning spool'),
    '#type' => 'textfield',
    '#default_value' => variable_get('notices_email_clean_spool_by_cron', 7),
    '#description' => t('Set periodicity in days'),
    '#size' => 5,
  );

  $form['notices_email_from_mail'] = array(
    '#title' => t('E-mail from address'),
    '#type' => 'textfield',
    '#default_value' => variable_get('notices_email_from_mail', variable_get('site_mail', '')),
  );

  $form['notices_email_mail_subject'] = array(
    '#title' => t('Subject for mail'),
    '#type' => 'textfield',
    '#description' => t('You can use tokens, which defines below'),
    '#default_value' => variable_get('notices_email_mail_subject', ''),
  );

  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('These tokens can be used in all text fields except subject and will be replaced on-screen and in the email.'),
    '#group' => 'additional_settings',
  );
  $form['help']['tokens'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('user', 'notices_node'),
  );

  $form['#validate'][] = 'notices_email_admin_settings_validate';

  return system_settings_form($form);
}


/**
 * Validate function.
 */
function notices_email_admin_settings_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['notices_email_letters_by_cron'])) {
    form_set_error('notices_email_letters_by_cron', t('You must enter integer value'));
  }

  if (!is_numeric($form_state['values']['notices_email_clean_spool_by_cron'])) {
    form_set_error('notices_email_clean_spool_by_cron', t('You must enter integer value'));
  }

  if (!valid_email_address($form_state['values']['notices_email_from_mail'])) {
    form_set_error('notices_email_from_mail', t('You must enter correct e-mail'));
  }
}
