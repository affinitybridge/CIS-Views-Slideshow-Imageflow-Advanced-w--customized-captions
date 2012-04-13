<?php
/**
 * @file
 * Default row template in cases when ImageFlow is not applied.
 *
 * - $vss_id: View ID.
 * - $classes: CSS classes.
 * - $items: Rendered fields.
 */
?>
<div id="views_slideshow_imageflow_advanced_div_<?php print $variables['vss_id']; ?>" class="<?php print $classes; ?>">
  <?php print $items;?>
</div>
