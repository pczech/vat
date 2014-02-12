<?php

/**
 * @file
 * Definition of dvc62_handler_field_zip_code.
 */


// @ignore sniffer_commenting_inlinecomment_spacingafter:file
// @ignore sniffer_namingconventions_validclassname_startwithcaptial:file
// @ignore style_class_names:file
// @ignore sniffer_namingconventions_validfunctionname_notlowercamel:file


/**
 * A field that displays zip code.
 */
class dvc62_handler_field_zip_code extends views_handler_field_field {

  /**
   * Define options of field zip code.
   */
  function option_definition() {
    vat_trace_funct();

    $options = parent::option_definition();

    $options['zip_total'] = array(
      'default' => FALSE,
      'bool' => TRUE,
    );

    // dpm($this, 'this');
    // dpm($options, 'options');

    return $options;
  }

  /**
   * Define form for field zip code options.
   */
  function options_form(&$form, &$form_state) {
    vat_trace_funct();

    parent::options_form($form, $form_state);
    // dpm($form, 'form');
    // dpm($form_state, 'form_state');
    // dpm($this, 'this');

    // Form id defined in options_form (zip_total) must be the same like option
    // id defined in option_definition - then it is automatically handled.
    $form['zip_total'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display Zip total'),
      '#description' => t('Appends in parentheses the number of nodes
          containing the same zip code'),
      '#default_value' => $this->options['zip_total'],
    );

    // dpm($form, 'form');
    // dpm($form_state, 'form_state');
  }

  /**
   * Render the field.
   */
  function render_item($count, $item) {
    if ($this->options['zip_total']) {
      $count = db_query("SELECT count(*) AS recs FROM {field_data_field_zip_code}
          WHERE field_zip_code_value = :zip", array(':zip' => $item['raw']['value']))
          ->fetchField();
    }

    return parent::render_item($count, $item) . ' (' . $count . ')';
  }
}
