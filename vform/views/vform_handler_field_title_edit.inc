<?php

/**
 * @file
 * Definition of vform_handler_field_title_edit.
 */

// @ignore sniffer_squiz_scope_methodscope_missing:file
// @ignore sniffer_functions_discouragedfunctions_discouraged:file
// @ignore sniffer_namingconventions_validfunctionname_notlowercamel:file
// @ignore style_class_names:file
// @ignore sniffer_namingconventions_validclassname_startwithcaptial:file
// @ignore sniffer_commenting_inlinecomment_spacingafter:file
// @ignore sniffer_files_linelength_toolong:file


module_load_include('inc', 'vat', 'includes/tools');

/**
 * Editable node title handler.
 */
class vform_handler_field_title_edit extends views_handler_field {
  /**
   * Construct a new editable title field handler.
   */
  public function construct() {
    parent::construct();
    // Make sure the node id and title values are loaded into the view. Title
    // is used as default value in Title form, nid is used to address the
    // corresponding records during databse update. See views_form() and
    // views_form_submit().
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['title'] = 'title';
  }


  /**
   * Override parent's query() not to add the editable field to the query.
   */
  function query() {
    $this->ensure_my_table();
    // Add additional_fields to the query. Field aliases are stored in
    // $this->aliases.
    $this->add_additional_fields();
  }


  /**
   * Render the field.
   *
   * The handler outputs a special placeholder in render():
   * <!--form-item-FIELD_ID--ROW_INDEX-->, while the real form with matching
   * structure gets added in views_form(). When the View is being preprocessed
   * for the theme file, all placeholders get replaced with the rendered form
   * elements.
   */
  function render($values) {
    // vat_trace_funct();
    // dpm($this->options);
    // dpm($this->view->row_index);

    // The below version is only for demonstration purposes and the production
    // solution can be much simple - like the following commented out line:
    // return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
    $form_element_name = $this->form_element_name();
    $form_element_row_id = $this->form_element_row_id($this->view->row_index);
    return '<!--form-item-' . $form_element_name . '--' . $form_element_row_id . '-->';
  }


  /**
   * Callback method for views_form_views_form().
   *
   * This is optional and can be used in case of complex field names.
   */
  function form_element_name() {
    // Make sure this value is unique for all the view fields.
    return $this->options['id'];
  }


  /**
   * Callback method for views_form_views_form().
   *
   * This is optional and can be used in case of complex row ids.
   */
  function form_element_row_id($row_id) {
    // You could use values from $this->view->result[$row_id]
    // to provide complex row ids.
    return $row_id;
  }


  /**
   * Alter the form created by Views.
   *
   * When Views sees that your field handler renders a comment like above (see
   * render() above), it will initialize and wrap a form around the view then
   * call your handlers views_form() method in the following way:
   *
   * -> view::render()
   * -> views_plugin_display::render()
   * -> theme()
   * -> template_preprocess_views_view() (*)
   * -> drupal_get_form()
   * -> views_form()
   * -> views_form_views_form()
   * -> vform_handler_field_title_edit::views_form()
   *
   * In order to get a form in Views, add your field replacements by creating a
   * container element with an index that matches the FIELD_ID. Then iterate
   * over the view result and add a form field element to the container for
   * every row in the view, using the row index as the element key in the
   * container. Views matches this form array structure to the corresponding
   * HTML comment to insert the field in the rendered View. In other words:
   * <!--form-item-FIELD_ID--ROW_INDEX--> is replaced by:
   * <?php $form[FIELD_ID][ROW_INDEX]; ?>
   *
   * (*) - see template theming example in pdd formex.
   */
  function views_form(&$form, &$form_state) {
    // vat_trace_funct();
    // dpm($form);
    // dpm($form_state);

    // dpm($this->view->result, '$this->view->result');
    // dpm($this->additional_fields, '$this->additional_fields');
    // dpm($this->aliases, '$this->aliases');

    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form_element_name = $this->form_element_name();

    // Create a container for the replacements.
    $form[$form_element_name] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    );

    // Iterate over the result and add the replacement fields to the form.
    foreach ($this->view->result as $row_id => $row) {
      $form_element_row_id = $this->form_element_row_id($row_id);
      // Add a text field to the form.  This array convention corresponds to
      // the placeholder HTML comment syntax.
      $form[$form_element_name][$form_element_row_id] = array(
        '#type' => 'textfield',
        '#default_value' => $row->{$this->aliases['title']},
        '#size' => 20,
        '#required' => TRUE,
      );
    }
    // dpm($form);
    // dpm($form_state);
  }

  /**
   * Title edit field validation handler.
   *
   * See views_form_views_form() and views_form_views_form_validate().
   */
  function views_form_validate($form, $form_state) {
    vat_trace_funct();
    // dpm($form);
    // dpm($form_state);

    $field_name = $this->form_element_name();
    foreach ($form_state['values'][$field_name] as $row_id => $value) {
      // Only allow titles where the first character is capitalized.
      if (!ctype_upper(substr($value, 0, 1))) {
        form_set_error($field_name . '][' . $row_id, t('All titles must be capitalized.'));
      }
    }
  }


  /**
   * Title edit field submit handler.
   *
   * See views_form_views_form() and views_form_views_form_submit().
   */
  function views_form_submit($form, $form_state) {
    vat_trace_funct();
    // dpm($this->view->result, 'this->view->result');
    // dpm($form_state['values'], 'values');

    // Determine which nodes we need to update.
    $updates = array();

    // Iterate over the view result.
    $field_name = $this->form_element_name();
    foreach ($this->view->result as $row_id => $row) {
      // Grab the correspondingly submitted form value.
      $value = $form_state['values'][$field_name][$row_id];
      // If the submitted value is different from the original value add it to
      // the array of nodes to update.
      if ($row->{$this->aliases['title']} != $value) {
        $updates[$row->{$this->aliases['nid']}] = $value;
      }
    }

    // Load the nodes we need to update and update them.
    $nodes = node_load_multiple(array_keys($updates));
    // dpm($nodes);
    foreach ($nodes as $nid => $node) {
      $node->title = $updates[$nid];
      node_save($node);
    }

    drupal_set_message(t('Updated @num node titles.',
        array('@num' => count($updates))));
  }
}
