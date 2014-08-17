<?php

/**
 * Output statuses for notice.
 *
 * @ingroup views_field_handlers
 */
class notices_handler_status extends views_handler_field_numeric {
  function render($values) {
    $status_output = array();
    $status = notices_getSendStatus($values);

    foreach ($status as $value) {
      $status_output[] = $value['status'];
    }

    return implode($status_output, ',');
  }
}
