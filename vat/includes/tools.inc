<?php

/**
 * @file
 * Common tools for VAT modules.
 */


// @ignore sniffer_commenting_inlinecomment_spacingafter:file
// @ignore sniffer_functions_discouragedfunctions_discouraged:file


/**
 * Traces function calls.
 */
function vat_trace_funct() {
  $trace = debug_backtrace();
  if (isset($trace[1])) {
    dpm($trace[1]['function']);
  }
}
