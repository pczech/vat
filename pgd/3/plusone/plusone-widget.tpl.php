<?php

/**
 * @file
 * template file for plusone widget.
 *
 * Available variables:
 *   $total - total number of votes
 *   $label - Vote widget label dependent of context, for example:
 *     'Vote' if user hasn't voted yet, it can be a link
 *     'You voted' if user hads already voted
 *     'Votes' if user is author of the content and can not vote.
 *
 *
 */

// Add the javascipt and CSS files
drupal_add_js(drupal_get_path('module', 'plusone') .'/plusone.js');
drupal_add_css(drupal_get_path('module', 'plusone') .'/plusone.css');

// Based on the attributes – display the appropriate label
// below the vote count.

?>

<div class="plusone-widget">
  <div class="score"> <?php print $total ?> </div>
  <div class="vote"> <?php print $label ?>  </div>
</div>
