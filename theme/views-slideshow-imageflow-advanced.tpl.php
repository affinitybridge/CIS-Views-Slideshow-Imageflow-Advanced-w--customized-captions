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
      $caption='<h3 class="species-commonname">'.$record->node_title.'</h3>';
      dpm ($record);
      // Scientific names
      if (isset($record->field_field_species_name_scientific[0]) && !empty($record->field_field_species_name_scientific[0]['rendered']['#markup'])) {
        $caption .= '<div class="species-scientificname"><span class="field-label">Scientific Name:&nbsp;</span>';
        $caption .= $record->field_field_species_name_scientific[0]['rendered']['#markup'];
        $caption .= '</div>';
      }

      // Other names
      if (isset($record->field_field_species_name_other) && !empty($record->field_field_species_name_other)) {
        $caption .= '<div class="species-othername"><span class="field-label">Other Name(s):&nbsp;</span>';
        $o_names = array();
        foreach ($record->field_field_species_name_other as $o_name) {
          $o_names[] = $o_name['rendered']['#markup'];
        }
        $caption .= implode(', ', $o_names);
        $caption .= '</div>';
      }
      
      // Species use
      if (count($record->field_field_cis_species_use)>0) {
        $caption .= '<div class="species-speciesuse"><span class="field-label">Species Use:&nbsp;</span>';
        foreach ($record->field_field_cis_species_use as $count => $use) {
          $caption .= $record->field_field_cis_species_use[$count]['rendered']['#markup'] . ", ";
        }
        $caption = substr($caption,0,-2);
        $caption .= '</div>';
      }
      
      // Public notes
      if (isset($record->field_field_cis_species_public_notes [0]) && !empty($record->field_field_cis_species_public_notes [0]['rendered']['#markup'])) {
        $caption .= '<div class="species-notes"><span class="field-label">Notes:&nbsp;</span>';
        $caption .= $record->field_field_cis_species_public_notes[0]['rendered']['#markup'];
        $caption .= '</div>';
      }
      
       // Translation
      foreach ($record->field_field_cis_translation as $trans_parent) {
        #dpm ($trans_parent, "translation parent");
        $trans_item=$trans_parent['rendered']['entity']['field_collection_item'][$trans_parent['raw']['value']];
        #dpm ($trans_item, "translation item");
        if ($language=$trans_item['field_cis_translation_lang'][0]['#title'] AND $name=$trans_item['field_cis_translation_name'][0]['#markup']) {
          $caption .= '<table class="species-translation"><tr>';
          $caption .= '<td class="field-value"><span class="field-label">' .$language. ':&nbsp;</span> ' . $name . '</td>';
          if (isset($trans_item['field_cis_translation_audio'][0]['#attributes']['src'])) {
            $caption.= '<td class="species-play">'.cis_species_playbutton($trans_item['field_cis_translation_audio'][0]['#attributes']['src']).'</td>';
          }
          $caption .= '</tr></table>';
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

