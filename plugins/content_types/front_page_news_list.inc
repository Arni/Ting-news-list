<?php
/**
 * @file result.inc
 * Provides search results as a Panels content type.
 */

/**
 * Callback function to supply a list of content types.
 *
 * This is only required to make CTools know that we're providing
 * multiple types here (since we have no single => TRUE in the array).
 */
function ting_news_list_front_page_news_list_ctools_content_types() {
  return array(
    'title' => t('Ting news list panel'),
    'single' => TRUE,
    'description' => t('A panel showing the most recently acquired materials'),
    'category' => t('Ting'),
  );
}

/**
 * Return the pane contents.
 */
function ting_news_list_front_page_news_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $path = drupal_get_path('module', 'ting_news_list');
  drupal_add_js($path . '/js/ting_news_list.js');
  drupal_add_js(array('tingNewsList' => array( 'destination' => drupal_get_destination())), 'setting', 'header');

  if (module_exists('jquery_ui') && module_exists('jquery_ui_theme')) {
      jquery_ui_add(array('ui.dialog', 'ui.tabs'));
      jquery_ui_theme_load();
  }
  $searches = variable_get('ting_news_list_searches', array());
  $block->content =  theme('ting_news_list_tabs', $searches); //'<div class="ting-news-box"><h3>' . ("Nyheder") . '</h3><div id="ting_news_list_placeholder"> </div></div>';
  return $block;

}



/**
 * Return the pane titles.
 */
function ting_news_list_front_page_news_list_content_type_admin_title($subtype, $conf, $context) {
  return t('News list panel');
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function ting_news_list_front_page_news_list_content_type_edit_form(&$form, &$form_state) {
  return $form;
}

?>
