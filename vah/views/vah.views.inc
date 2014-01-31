<?php

/**
 * @file
 * Views extensions for VAH module.
 */

/**
 * Implementes hook_views_data().
 */
function vah_views_data() {
  vat_trace_funct();

  $data['views']['collapsible_area'] = array(
    'title' => t('Collabsible Text area'),
    'help' => t('Provide collabsible markup text for the area.'),
    'area' => array(
      'handler' => 'vah_handler_collapsible_area_text',
    ),
  );

  return $data;
}
