<?php
/**
 * @file
 * Drush support for node_export.
 */

/**
 * Implements hook_drush_command().
 */
function notices_email_drush_command() {
  $items = array();

  $items['notices_email'] = array(
    'callback' => 'drush_notices_email_callback',
    'description' => "Invoke notices_email jobs.",
    'arguments' => array(
      'type' => 'no argumet\'s yet.',
    ),
    'examples' => array(
      'drush notices_email' => 'Invoke notices_email jobs.',
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function notices_email_drush_help($section) {
  switch ($section) {
    case 'drush:notices_email':
      return dt("Invoke notices_email jobs.");
  }
}

/**
 * Drush command callback.
 */
function drush_notices_email_callback() {
  drush_print(dt('We will process notices_email spool '));
  if (drush_confirm(dt('You really want to continue?'))) {
    notices_email_spool();
  }
}
