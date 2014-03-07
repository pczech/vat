<?php

/**
 * @file
 * Views extensions for VFORM module.
 */


/**
 * Implements hook_views_data_alter().
 */
function vform_views_data_alter(&$data) {
  vat_trace_funct();
  // dpm($data);

  $data['node']['title_edit'] =  array(
    'field' => array(
      'title' => t('Title form field'),
      'help' => t('Edit the node title'),
      'handler' => 'vform_handler_field_title_edit',
    ),
  );
}
