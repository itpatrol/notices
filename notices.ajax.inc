<?php

function notices_remove_ajax($notice_id, $count) {
  global $user;

  $notice = noticeid_load($notice_id);
  if ($user->uid == $notice->uid) {
    notices_delete($notice_id);
  }
  else {
    $admin_uid = variable_get('pg_account_admin_uid', '1');
    if (!empty($admin_uid)) {
      // Notify admin about balance update.
      $noticeadmin = new stdClass();
      $noticeadmin->uid = $admin_uid;

      $noticeadmin->teaser = t('Hack attempt from !uid (!IP) to !noticeid', array(
        '!uid' => $user->uid,
        '!noticeid' => $notice_id,
        '!IP' => $user->hostname,
      ));

      $noticeadmin->body = t('Hack attempt from !uid (!IP) to !noticeid', array(
        '!uid' => $user->uid,
        '!noticeid' => $notice_id,
        '!IP' => $user->hostname,
      ));

      $noticeadmin->callback = 'notice';

      notices_save($noticeadmin);
    }

    print drupal_to_js(array(
      'status' => TRUE,
      'data' => t('You are trying to hack our system. We sent notification about this action to system administrator.'),
    ));

    drupal_exit();
  }

  $output = '';
  $notice_sql = 'SELECT * FROM {notices} WHERE uid=%d ORDER BY new DESC,timestamp DESC LIMIT %d OFFSET %d';
  $notice_result = db_query($notice_sql, $user->uid, 1, $count);
  
  if ($notice = db_fetch_object($notice_result)) {
    $output .= '<div id="notices">';
    $output .= theme('notices_view_teaser', $notice);
    $output .= "</div>";
  }

  print drupal_to_js(array('status' => TRUE, 'data' => $output));
  drupal_exit();
}

function notices_mark_read_ajax($notice_id = NULL) {
  global $user;

  if ($notice_id == 'all') {
    db_update('notices')
      ->fields(array(
        'new' => '0',
      ))
      ->condition('uid', $user->uid, '=')
      ->execute();
  }
  else {
    db_update('notices')
      ->fields(array(
        'new' => '0',
      ))
      ->condition('noticeid', $notice_id, '=')
      ->condition('uid', $user->uid, '=')
      ->execute();
  }

  return;
}

function notices_load_ajax() {
  global $user;

  $output = '';

  $notice = db_select('notices', 'n')
    ->fields('n')
    ->condition('uid', $user->uid, '=')
    ->orderBy('new', 'DESC')
    ->orderBy('timestamp', 'DESC')
    ->range(2, 1)
    ->execute()
    ->fetchObject();

  $output .= '<div id="notices">';
  $output .= theme('notices_view_teaser', $notice);
  $output .= '</div>';

  print drupal_to_js(array('status' => TRUE, 'data' => $output));
  drupal_exit();
}