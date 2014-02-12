<?php

/**
 * @file
 * Definition of dvc63_handler_field_zip_code.
 */


// @ignore sniffer_commenting_inlinecomment_spacingafter:file
// @ignore sniffer_namingconventions_validclassname_startwithcaptial:file
// @ignore style_class_names:file
// @ignore sniffer_namingconventions_validfunctionname_notlowercamel:file


/**
 * A field that displays zip code.
 */
class dvc63_handler_field_zip_code extends views_handler_field_field {

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

    $options['zip_type'] = array(
      'default' => 3,
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

    $form['zip_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('ZIP settings'),
    );

    // Disable 'type' form and move it to ZIP setting fieldset.
    $form['type'] += array(
      '#disabled' => TRUE,
      '#weight' => 1,
      '#fieldset' => 'zip_settings',
    );

    $form['zip_type'] = array(
      '#type' => 'select',
      '#title' => t('ZIP formatter'),
      '#options' => array(
        1 => t('Zip+4'),
        2 => t('Zip'),
        3 => t('Alphanumeric'),
      ),
      '#default_value' => $this->options['zip_type'],
      '#weight' => 2,
      '#fieldset' => 'zip_settings',
    );

    // Form id defined in options_form (zip_total) must be the same like option
    // id defined in option_definition - then it is automatically handled.
    // Thus, fielset cannot be used like $form['zip_settings]['zip_total'],
    // use '#fieldset' parameter instead.
    $form['zip_total'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display Zip total'),
      '#description' => t('Appends in parentheses the number of nodes
          containing the same zip code'),
      '#default_value' => $this->options['zip_total'],
      '#weight' => 3,
      '#fieldset' => 'zip_settings',
    );

    // dpm($form, 'form');
    // dpm($form_state, 'form_state');
  }

  /**
   * Render the field.
   */
  function render_item($count, $item) {
    $ret = parent::render_item($count, $item);
    $ret = $this->renderZip($ret);

    if ($this->options['zip_total']) {
      $count = db_query("SELECT count(*) AS recs FROM {field_data_field_zip_code}
          WHERE field_zip_code_value = :zip", array(':zip' => $item['raw']['value']))
          ->fetchField();

      $ret .= ' (' . $count . ')';
    }

    return $ret;
  }

  /**
   * Render zip code.
   */
  protected function renderZip($zip) {
    // Remove the hyphen if present.
    $zip_t = str_replace('-', '', $zip);
    $zip_t .= 'XXXXXXXXX';

    switch ($this->options['zip_type']) {
      case 1:
        $zip = substr($zip_t, 0, 5) . '-' . substr($zip_t, 5, 4);
        break;

      case 2:
        $zip = substr($zip_t, 0, 5);
        break;

      case 3:
        // No format change.
        break;
    }

    return $zip;
  }
}
