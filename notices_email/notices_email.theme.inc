<?php
/**
 * @file
 * Theme functions for module.
 */

/**
 * Processes variables for notices-email-view.tpl.php.
 *
 * @param array $vars
 *   An associative array containing the following key:
 *   - notice.
 *
 * @see notices-email-view.tpl.php
 */
function template_preprocess_notices_email_view(&$vars) {
  $notice = $vars['notice'];

  $vars['content'] = check_markup($notice->message, $notice->format, FALSE);

  $links[] = array(
    'title' => t('Read more'),
    'href' => 'notices/view/' . $notice->noticeid,
    'attributes' => array(
      'class' => 'notice-read-more',
    ),
  );

  $links[] = array(
    'title' => t('Mark as read'),
    'href' => 'notices/read/' . $notice->noticeid,
    'attributes' => array(
      'rel' => $notice->noticeid,
      'id' => 'noticeread-' . $notice->noticeid,
      'class' => 'notice-mark-read',
    ),
  );

  $links[] = array(
    'title' => t('Delete'),
    'href' => 'notices/delete/' . $notice->noticeid,
    'attributes' => array(
      'rel' => $notice->noticeid,
      'id' => 'noticeremove-' . $notice->noticeid,
      'class' => 'notice-remove',
    ),
  );

  $vars['time'] = format_date($notice->timestamp, 'medium');

  $variables = array(
    'links' => $links,
    'attributes' => array('class' => 'notice-links'),
  );

  $vars['links'] = theme('links', $variables);

  $file = drupal_get_path('module', $notice->provider) . '/' . $notice->provider . '.png';
  if (!file_exists($file)) {
    $file = drupal_get_path('module', 'notices') . '/default.png';
  }
  $vars['picture'] = $file;
}
