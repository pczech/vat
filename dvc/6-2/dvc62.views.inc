<?php

/**
 * @file
 * Views hooks for DVC62 module.
 */

module_load_include('inc', 'vat', 'includes/tools');

/**
 * Implements hook_views_data_alter()
 */
function dvc62_field_views_data_alter(&$result, $field, $module) {
  vat_trace_funct();
  // dpm($result, 'result');
  // dpm($field, 'field');
  // dpm($module, 'module');

  if (array_key_exists('field_data_field_zip_code', $result)) {
    dpm($result, 'result');
    dpm($field, 'field');
    dpm($module, 'module');
    // Overwrite the field handler for ZIP Code field.
    $result['field_data_field_zip_code']['field_zip_code']['field']['handler']
      = 'dvc62_handler_field_zip_code';
  }
}
