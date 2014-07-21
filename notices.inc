<?php
// $Id$

function notices_list($account = null){
  drupal_add_js(drupal_get_path('module', 'notices') .'/notices.js');
  drupal_add_css(drupal_get_path('module', 'notices') .'/notices.css');
  
  if(!is_object($account)){
    global $user;
    $account = $user;
  }
  
//  $filters = formfilterapi_build_filter_query('notices_list');
  $header = array(
    array('data' => t('Date'), 'field' => 'timestamp', 'sort' => 'desc'),
    array('data' => t('Subject'), 'field' => 'subject'),
  );
  if(empty($filters['where'])){
    $filters['where'] = "WHERE uid='".$account->uid."'";
  } else {
    $filters['where'] .= " AND uid='".$account->uid."'";
  }
  
  $notices = db_select('notices', 'n')->extend('AltPager')
    ->fields('n')
    ->orderBy('timestamp', 'DESC')
    ->execute()
    ->fetchAll();

  $output_notices = '';
  foreach ($notices as $notice) {
    $output_notices .= theme('notices_view_teaser', array('notice' => $notice));
  }//while

  if(empty($output_notices)){
    $output_notices =  t('No notifications.');
  }
  $pagerCountShow = theme('altpager');
//  $output .= formfilterapi_getForm('notices_list');
  $links = array (
    'links' => array (
      array(
        'href' => 'notices/mark-as-read',
        'title' => t('Mark as Read'),
        'attributes' => array('id' => 'notices-mark-as-read'),
      ),
      array(
        'href' => 'notices/settings',
        'title' => t('Settings'),
      ),

    ),
    'attributes' => array('class' => 'notices-links'),
  );
  $output = theme('links',$links);
  $output .= $pagerCountShow;
  $output .= '<div id="notices" >';
  $output .=  $output_notices;
  $output .= "</div>";
  $output .= $pagerCountShow;
  
  return $output;

}


function notices_view($notice){
  drupal_add_css(drupal_get_path('module', 'notices') .'/notices.css');

  $output = '<div id="notices">';
  $output .= theme('notices_view', array('notice' => $notice));
  $output .= "</div>";

  if($notice->new){
    notices_mark_read($notice);
  }
  
  return $output;
}

function notices_delete_form($form, &$form_state,$notice){
  $form['noticeid'] = array (
    '#type' => 'value',
    '#value' => $notice->noticeid,
  );
  $form['alert'] = array (
    '#markup' => t('Do you want to delete this message?'),
  );
  $form['message'] = array (
    '#markup' => check_markup($notice->message, $notice->format, FALSE),
  );
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Delete'),
  );
  return $form;
}

function notices_delete_form_submit($form, &$form_state){
  global $user;
  notices_delete($form_state['values']['noticeid']);
  drupal_goto('notices');
}

function notices_settings($form, &$form_state){
  global $user;
  
  $settings = notices_load_settings($user->uid);
  
  $sendOptions=array();
  $sendOptionsSettings=array();
  foreach (module_implements('sendNotice') as $name) {
    $function = $name . '_sendNotice';
    $op="settings";
    $result = $function($op);
    $sendOptions[$name] = $result['title'];
    $sendOptionsSettings[$name] = $result;
  }//foreach

  $provideOptions=array();
  foreach (module_implements('provideNotice') as $name) {
    $function = $name . '_provideNotice';
    $op="settings";
    $result = $function($op);
    $provideOptions[$name] = $result;
  }//foreach
  

  $form['providers']=array(
    '#tree' => true,
  );

  foreach($provideOptions as $provider){
    $form['providers'][$provider['name']] = array(
      '#type'  => 'fieldset',
      '#title' => $provider['title'],
      '#tree'  => true,
    );  
    foreach($sendOptions as $name => $title){
      $form['providers'][$provider['name']][$name] = array(
        '#type'  => 'fieldset',
        '#title' => $title,
        '#tree'  => true,
      );
      $form['providers'][$provider['name']][$name]['active'] = array(
        '#type'  => 'checkbox',
        '#title' => t('Activate'),
        '#default_value' => $settings->settings[$provider['name']][$name]['active'],
      );
      $form['providers'][$provider['name']][$name]['values'] = $sendOptionsSettings[$name]['values'];
      foreach($sendOptionsSettings[$name]['values'] as $sendName => $value){
        if(!empty($settings->settings[$provider['name']][$name]['values'][$sendName])){
          $form['providers'][$provider['name']][$name]['values'][$sendName]['#default_value'] = $settings->settings[$provider['name']][$name]['values'][$sendName];
        }  
      }
      
    }
    
  }
  
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save changes'),
  );
  return $form;
}

function notices_settings_submit($form, &$form_state){
  global $user;

  $settings = notices_load_settings($user->uid);
  
  $settings->settings = serialize($form_state['values']['providers']);
  
  if($settings->is_empty){
    drupal_write_record('notices_settings',$settings);
  }else{
    drupal_write_record('notices_settings',$settings,'uid');
  }
  drupal_set_message(t('Changes saved'));
}

function notices_mark_as_read(){
  global $user;
  db_query("UPDATE {notices} set new=0 WHERE uid = :uid", array(':uid' => $user->uid));
  drupal_goto('notices');
}