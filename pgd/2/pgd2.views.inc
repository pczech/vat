<?php

/**
 * @file
 * Views hooks for PGD module.
 */


// @ignore sniffer_commenting_inlinecomment_spacingafter:file


/**
 * Implements hook_views_data().
 */
function pgd2_views_data() {
  vat_trace_funct();

  $data['giant_rabbits']['table']['group'] = t('VAT');

  $data['giant_rabbits']['table']['base'] = array(
    'field' => 'bid',
    'title' => t('Bunny'),
    'help' => t('Giant rabbits'),
  );

  $data['giant_rabbits']['bid'] = array(
    'title' => t('Bid'),
    'help' => t('The bunny ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['giant_rabbits']['name'] = array(
    'title' => t('Name'),
    'help' => t('The bunny name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['giant_rabbits']['tons'] = array(
    'title' => t('Tons'),
    'help' => t('The bunny weight in tons.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  return $data;
}
