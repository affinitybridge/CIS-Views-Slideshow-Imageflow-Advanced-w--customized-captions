<?php
/**
 *highly customized for affinity bridge's slideshow caption, based on http://drupal.org/node/671252
 *
 */
?>
<?php if (isset($images) && !empty($images)) : ?>
<?php $desc= array(); ?>
<div id="views-slideshow-imageflow-advanced-<?php print $id; ?>" class="views-slideshow-imageflow-advanced">
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>

  <div id="views-slideshow-imageflow-advanced-images-<?php print $id; ?>" class="views-slideshow-imageflow-advanced-images imageflow">
    <?php
    foreach ($images as $key => $image) {
      print  $image ."\n";
      $record=$view->result[$key];
      $caption='<div class="species-commonname">'.$record->node_title.'</div>';

      foreach ($record->field_field_cis_translation as $trans_parent) {
        #dpm ($trans_parent, "translation parent");
        $trans_item=$trans_parent['rendered']['entity']['field_collection_item'][$trans_parent['raw']['value']];
        #dpm ($trans_item, "translation item");
        if ($language=$trans_item['field_cis_translation_lang'][0]['#title'] AND $name=$trans_item['field_cis_translation_name'][0]['#markup']) {
          $caption .= '<div class="species-translation">' .$language. ': '.$name;
          if (isset($trans_item['field_cis_translation_audio'][0]['#file']->uri)) {
            $audio='/'.variable_get('file_public_path', conf_path() . '/files').'/'.substr($trans_item['field_cis_translation_audio'][0]['#file']->uri,9);
            $caption.= '<span class="species-play">'.cis_species_playbutton($audio).'</span>';
          }
          $caption .= '</div>';
        }
      }
      $desc[]=$caption;
    } ?>
  </div>
</div>
<?php
drupal_add_js(array('customshow' => $desc), 'setting');?>
<div id='customshow-breakout'></div>
<?php endif;?>

