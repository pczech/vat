<?php

/**
 * @file
 * Views hooks for PGD module.
 */


/**
 * Implements hook_views_data().
 */
function pgd1_views_data() {
  vat_trace_funct();

  $data = array(
    // Info about the table named 'login_history'.
    'login_history' => array(
      // Special item 'table'
      'tabe' => array(
        'group' => t('View API Training'),
        /*
         This cannot be a base table.
        'base' => array(
        ),
        */
        'join' => array(
          'users' => array(
            // Directly links to users table.
            'left_field' => 'uid',
            'field' => 'uid',
          ),
        ),
      ),
      // Info about the field named 'uid'.
      'uid' => array(
        'title' => t('PGD Uid'),
        'help' => t('PGD The User ID'),
        /*
        'argument' =>,
        'field' =>,
        'filter' =>
        'relationship' =>
        'sort' =>
        */
      ),
      // Info about the field named 'login'.
      'login' => array(
        'title' => t('PGD login'),
        'help' => t('PGD Login timestamp'),
      ),
     ),
    // Info about the table named 'login_history'
    // ...
  );

  return $data;
}
