<?php
/**
 * @file
 * Provide views data for notices.module.
 */

/**
 * Implements of hook_views_data().
 */
function notices_views_data() {
  $data['notices'] = array(
    'table' => array(
      'base' => array(
        'field' => 'noticeid',
        'title' => 'Notices',
        'help' => 'notices holds the message information',
      ),
      'group' => 'Notices',
      'join' => array(
        'node' => array(
          'left_field' => 'nid',
          'field' => 'nid',
        ),
      ),
    ),
    'noticeid' => array(
      'title' => 'Noticeid',
      'help' => 'Primary Key: Unique notice ID.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'uid' => array(
      'title' => 'Uid',
      'help' => 'The users.uid of the user who will receive the notice.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
      'relationship' => array(
        'base' => 'users',
        'base field' => 'uid',
        'handler' => 'views_handler_relationship',
        'label' => t('recipient'),
        'title' => t('Recipient'),
        'help' => t('Relate notice to the user who will receive the notice.'),
      ),
    ),
    'provider' => array(
      'title' => 'Provider',
      'help' => 'Module system name that triggered this notification',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
    ),
    'message' => array(
      'title' => 'Message',
      'help' => 'Text of notice.',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
    ),
    'new' => array(
      'title' => 'New',
      'help' => 'The flag for unread notice.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
    ),
    'format' => array(
      'title' => 'Format',
      'help' => 'The filter_format.format of the signature.',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
    ),
    'timestamp' => array(
      'title' => 'Timestamp',
      'help' => 'Unix timestamp of when notice created.',
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
    ),
  );

  return $data;
}
