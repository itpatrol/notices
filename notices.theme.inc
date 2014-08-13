<?php
/**
 * @file
 * Provides theme functions.
 */

/**
 * Processes variables for notices-view.tpl.php.
 *
 * @param array $vars
 *   An associative array containing the following key:
 *   - notice.
 *
 * @see notices-view.tpl.php
 */
function template_preprocess_notices_view(&$vars) {
  $notice = $vars['notice'];
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
  $vars['content'] = check_markup($notice->message, $notice->format, FALSE);
  $variables = array(
    'links' => $links,
    'attributes' => array('class' => 'notice-links'),
  );
  $vars['links'] = theme('links', $variables);
  $vars['timeago'] = t('@time ago', array('@time' => format_interval(REQUEST_TIME - $notice->timestamp)));

  $file = drupal_get_path('module', $notice->provider) . '/' . $notice->provider . '.png';
  if (!file_exists($file)) {
    $file = drupal_get_path('module', 'notices') . '/default.png';
  }

  $vars['picture'] = $file;
  $status_output = '';
  $status = notices_getSendStatus($notice);
  foreach ($status as $name => $value) {
    $status_output .= '<li class="' . $name . '" style="background: url(/' . $value['icon'] . ') no-repeat center left; padding-left: 22px;"><span class="status">' . $value['status'] . '</span></li>';
  }

  if (!empty($status_output)) {
    $vars['status'] = '<ul class="notices_status">' . $status_output . '</ul>';
  }
}

/**
 * Processes variables for notices-view.tpl.php.
 *
 * @param array $vars
 *   An associative array containing the following key:
 *   - notice.
 *
 * @see notices-view-teaser.tpl.php
 */
function template_preprocess_notices_view_teaser(&$vars) {
  $notice = $vars['notice'];
  $res = explode("\n", $notice->message);

  if (count($res) > 5) {
    $notice->message = $res = $res[0] . "\n" . $res[1] . "\n" . $res[2] . "\n" . $res[3] . "\n" . $res[4] . "\n";
  }

  $vars['content'] = check_markup($notice->message, $notice->format, FALSE);

  $links[] = array(
    'title' => t('Read more'),
    'href' => 'notices/view/' . $notice->noticeid,
    'attributes' => array(
      'class' => 'notice-read-more',
    ),
  );

  if ($notice->new) {
    $links[] = array(
      'title' => t('Mark as read'),
      'href' => 'notices/read/' . $notice->noticeid,
      'attributes' => array(
        'rel' => $notice->noticeid,
        'id' => 'noticeread-' . $notice->noticeid,
        'class' => 'notice-mark-read',
      ),
    );
  }

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
  $vars['timeago'] = t('@time ago', array('@time' => format_interval(REQUEST_TIME - $notice->timestamp)));

  $file = drupal_get_path('module', $notice->provider) . '/' . $notice->provider . '.png';
  if (!file_exists($file)) {
    $file = drupal_get_path('module', 'notices') . '/default.png';
  }
  $vars['picture'] = $file;
  $status_output = '';
  $status = notices_getSendStatus($notice);
  foreach ($status as $name => $value) {
    $status_output .= '<li class="' . $name . '" style="background: url(/' . $value['icon'] . ') no-repeat center left; padding-left: 22px;"> <span class="status">' . $value['status'] . '</span></li>';
  }
  if (!empty($status_output)) {
    $vars['status'] = '<ul class="notices_status">' . $status_output . '</ul>';
  }
}
