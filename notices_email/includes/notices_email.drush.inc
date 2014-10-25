<?php

/**
 * @file
 * Sending email by Drush command.
 */

/**
 * Implements hook_drush_command().
 */
function notices_email_drush_command() {
  $items = array();

  $items['notices-email-send'] = array(
    'description' => dt('Sending mails from the pool.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'callback' => 'notices_email_drush_sending_mail',
  );

  return $items;
}

/**
 * Sending mails from the pool.
 */
function notices_email_drush_sending_mail() {
  $count = notices_email_spool();

  drush_print(dt('@count_success email has been sent. @count_error email was not sent.', array(
    '@count_success' => $count['success'],
    '@count_error' => $count['error'],
  )));
}
