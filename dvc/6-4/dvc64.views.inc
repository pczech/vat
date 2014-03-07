<?php

/**
 * @file
 * Views hooks for DVC64 module.
 */

// @ignore sniffer_commenting_inlinecomment_spacingafter:file
// @ignore sniffer_functions_discouragedfunctions_discouraged:file

module_load_include('inc', 'vat', 'includes/tools');


/**
 * Implements hook_field_views_data_alter().
 */
function dvc64_field_views_data_alter(&$result, $field, $module) {
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
      = 'dvc64_handler_field_zip_code';
  }
}


/**
 * Implements hook_views_query_alter().
 */
function dvc64_views_query_alter(&$view, &$query) {
  vat_trace_funct();
  if ($view->name == 'zip_codes_3') {
    // dpm($view, 'view');
    // dpm($query, 'query');
    $query->orderby[0]['field'] = 'nid';
    $query->orderby[0]['direction'] = 'ASC';
  }
}
