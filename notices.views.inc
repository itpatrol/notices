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
        'title' => t('Notices'),
        'help' => 'notices holds the message information',
      ),
      'group' => t('Notices'),
      'join' => array(
        'node' => array(
          'left_field' => 'nid',
          'field' => 'nid',
        ),
      ),
    ),
    'noticeid' => array(
      'title' => 'Noticeid',
      'help' => t('Primary Key: Unique notice ID.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'uid' => array(
      'title' => t('Uid'),
      'help' => t('The users.uid of the user who will receive the notice.'),
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
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
    ),
    'provider' => array(
      'title' => t('Provider'),
      'help' => t('Module system name that triggered this notification'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
    ),
    'message' => array(
      'title' => t('Message'),
      'help' => t('Text of notice.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
    ),
    'new' => array(
      'title' => t('New'),
      'help' => t('The flag for unread notice.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'format' => array(
      'title' => t('Format'),
      'help' => t('The filter_format.format of the signature.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
    ),
    'timestamp' => array(
      'title' => t('Timestamp'),
      'help' => t('Unix timestamp of when notice created.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
  );

  return $data;
}
