<?php

/**
 * Implements hook_token_info().
 */
function notices_node_token_info() {
  $info['types']['notices_node'] = array(
    'name' => t('Notices'),
    'description' => t('Tokens related to notice.'),
    'needs-data' => 'notices_node',
  );

  // Tokens.
  $info['tokens']['notices_node']['uid'] = array(
    'name' => t('uid'),
    'description' => t("The unique uid of the user who receive notice."),
  );

  $info['tokens']['notices_node']['mail'] = array(
    'name' => t('mail'),
    'description' => t("The mail address of the user who receive notice."),
  );
  $info['tokens']['notices_node']['username'] = array(
    'name' => t('username'),
    'description' => t("The username of the user who receive notice."),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function notices_node_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);
  if (isset($data['notices_node'])) {
    $replace = (object) $data['notices_node'];

    if ($type == 'notices_node') {
      foreach ($tokens as $name => $original) {
        switch ($name) {
          case 'uid':
            $replacements[$original] = $replace->uid;
            break;

          case 'mail':
            $replacements[$original] = $sanitize ? check_plain($replace->mail) : $replace->mail;
            break;

          case 'username':
            $replacements[$original] = $sanitize ? check_plain($replace->username) : $replace->username;
            break;
        }
      }
    }
  }
  return $replacements;
}
