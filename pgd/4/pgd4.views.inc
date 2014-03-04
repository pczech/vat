<?php

/**
 * @file
 * Views hooks for PGD module.
 */


// @ignore sniffer_commenting_inlinecomment_spacingafter:file


/**
 * Implements hook_views_plugins().
 */
function pgd4_views_plugins() {
  vat_trace_funct();

  $plugins = array();

  return $plugins;
}


/**
 * Implements hook_views_plugins_alter().
 */
function pgd4_views_plugins_alter(&$plugins) {
  vat_trace_funct();

  dpm($plugins);
}
