<?php

/**
 * @file
 * Views hooks for PGD module.
 */


// @ignore sniffer_commenting_inlinecomment_spacingafter:file


/**
 * Implements hook_views_data().
 */
function pgd1_views_data() {
  vat_trace_funct();

  // Info about the table named 'login_history'.
  $data['login_history']['table']['group'] = t('VAT');

  // This cannot be a base table, as it has no primary field.
  // $data['login_history']['table']['base'] = ...,

  // Define how this table joins to others. The table joins to users table and
  // in result the fields are available in type of data 'user'.
  $data['login_history']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // Info about the fields.
  // The field is visible, if ['field']['handler'] is specified. Here uid is
  // really not necessary as it doubles Uid defined by user_views_data().
  $data['login_history']['uid'] = array(
    'title' => t('Uid'),
    'help' => t('The user id'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
  );

  $data['login_history']['login'] = array(
    'title' => t('Login'),
    'help' => t('Login timestamp from login history.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
  );

  return $data;
}
