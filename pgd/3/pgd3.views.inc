<?php

/**
 * @file
 * Views hooks for PGD module.
 */


// @ignore sniffer_commenting_inlinecomment_spacingafter:file


/**
 * Implements hook_views_data().
 */
function pgd3_views_data() {
  vat_trace_funct();

  $data['plusone_votes']['table']['group'] = t('VAT');

  // The table must have single primary field to be base table. So
  // plusone_votes can not be base table, as it has composite primary key.

  $data['plusone_votes']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['plusone_votes']['uid'] = array(
    'title' => t('Voter uid'),
    'help' => t('The user who voted the content. If you need more fields than the uid add the content: voter relationship'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
    ),
    'relationship' => array(
      'title' => t('Voter'),
      'help' => t('Relate content to the user who voted it.'),
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('voter'),
    ),
  );

  $data['plusone_votes']['vote_count'] = array(
    'title' => t('Votes'),
    'help' => t('The voutes count.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
