<?php

/**
 * @file
 * Definition of vform_handler_field_title_edit.
 */

// @ignore sniffer_squiz_scope_methodscope_missing:file
// @ignore sniffer_functions_discouragedfunctions_discouraged:file
// @ignore sniffer_namingconventions_validfunctionname_notlowercamel:file

/**
 * Editable node title handler.
 */
class vform_handler_field_title_edit extends views_handler_field {
  /**
   * Construct a new editable title field handler.
   *
   * Make sure the node id and title values are loaded into the view. Title is
   * used as default value in Title form. See views_form().
   */
  public function construct() {
    parent::construct();
    // $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['title'] = 'title';
  }


  /**
   * Override parent's query() not to add the editable field to the query.
   */
  function query() {
    $this->ensure_my_table();
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
    dpm(__FUNCTION__);
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
    // Make sure this value is unique for all the view fields
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

  //TODO: Add description, see views_form_views_form()
  // drupal_get_form() -> hook_forms() -> views_forms() -> sets form callback to view -> views_form() ->
  function views_form(&$form, &$form_state) {
    dpm(__FUNCTION__);
    dpm($form);
    dpm($form_state);

    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form_element_name = $this->form_element_name();

    // Create a container for the replacements
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
        //'#element_validate' => array('view_form_field_handler_title_edit_validate'),
        '#required' => TRUE,
      );
    }
    dpm($form);
    dpm($form_state);
  }
}
