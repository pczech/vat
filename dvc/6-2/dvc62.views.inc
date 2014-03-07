<?php

/**
 * @file
 * Views hooks for DVC62 module.
 */

// @ignore sniffer_commenting_inlinecomment_spacingafter:file
// @ignore sniffer_functions_discouragedfunctions_discouraged:file

module_load_include('inc', 'vat', 'includes/tools');

/**
 * Implements hook_field_views_data_alter().
 */
function dvc62_field_views_data_alter(&$result, $field, $module) {
  vat_trace_funct();
  // dpm($result, 'result');
  // dpm($field, 'field');
  // dpm($module, 'module');

  if (array_key_exists('field_data_field_zip_code', $result)) {
    // dpm($result, 'result');
    // dpm($field, 'field');
    // dpm($module, 'module');
    // Overwrite the field handler for ZIP Code field. Default handler for
    // fields built by Field API is views_handler_field_field.
    $result['field_data_field_zip_code']['field_zip_code']['field']['handler']
      = 'dvc62_handler_field_zip_code';
  }
}
