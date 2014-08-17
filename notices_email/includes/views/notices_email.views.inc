<?php
/**
 * @file
 * Provide views data for notices_email.module.
 */

/**
 * Implements of hook_views_data().
 */
function notices_email_views_data() {
  $data['notices_email_status']['table']['join']['notices'] = array(
    'left_field' => 'noticeid',
    'field' => 'noticeid',
  );

  $data['notices_email_status']['status'] = array(
    'title'  => t('Status of send'),
    'help'   => t('Status of sending notification e-mail client.'),
    'group'  => t('Notices'),
    'field'  => array('handler' => 'notices_handler_status'),
    'sort'   => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
  );

  return $data;
}
