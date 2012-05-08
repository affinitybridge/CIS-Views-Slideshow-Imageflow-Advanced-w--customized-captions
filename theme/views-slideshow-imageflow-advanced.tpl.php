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
      
      // Scientific name
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
      foreach ($record->field_field_cis_translation as $index => $trans_parent) {
        $trans_item=$trans_parent['rendered']['entity']['field_collection_item'][$trans_parent['raw']['value']];
        if (isset($trans_item['field_cis_translation_lang'][0]['#title']) AND isset($trans_item['field_cis_translation_name'][0]['#markup'])) {
          $language=$trans_item['field_cis_translation_lang'][0]['#title'];
          $name=$trans_item['field_cis_translation_name'][0]['#markup'];
          
          $caption .= '<table class="species-translation"><tr>';
          $caption .= '<td class="field-value"><span class="field-label">' .$language. ':&nbsp;</span> ' . $name . '</td>';
          
          //audio file
          if (isset($trans_item['field_cis_translation_audio'][0]['#attributes']['src'])) {
            $caption.= '<td class="species-play">'.cis_species_playbutton($trans_item['field_cis_translation_audio'][0]['#attributes']['src']).'</td>';
          }
          
          // video popup
          if (isset($trans_item['field_cis_translation_video'][0]['#attributes']['src'])) {
            //module_load_include('inc', 'popup', 'includes/popup.api');
            //$caption.= '<td>'.popup_element('video', '<video width="360" height="203" id="video'.$index.'" src="' . $trans_item['field_cis_translation_video'][0]['#attributes']['src'] . '">Cannot play video</video>', array('activate' => 'click')).'</td>';
            $caption .= '<td>'.
              l(t('Video'), $trans_item['field_cis_translation_video'][0]['#attributes']['src'], array('attributes' => array('rel' => 'lightvideo[group][Language: ' . $language. ' - Name: ' . $name . ']'))) .
              '</td>';
            
            /*/ testing:
            if($record->nid == 68) {
            // create video settings for mediaelement video theme function
            $video = array(
              'attributes' => array(
                'src' => $trans_item['field_cis_translation_video'][0]['#attributes']['src'],
                'class' => 'mediaelement-formatter-identifier-' . $trans_parent['raw']['value'],
                'controls' => 'controls',
                'height' => '360',
                'width' => '203',
                'preload' => 'true',
              ),
              'settings' => array(
                'controls' => 1,
                'download_link' => 0,
                'download_text' => t("Download"),
                'height' => '360',
                'width' => '203',
              ),
            );
            //print popup_element('Video', theme('mediaelement_video', $video), array('activate' => 'click'));
            //print '<a href="' . $trans_item['field_cis_translation_video'][0]['#attributes']['src'] . '" rel="lightvideo[][Language: ' . $language. ' - Name: ' . $name . ']">Video test</a>';
            print l(t('Video test 2'), $trans_item['field_cis_translation_video'][0]['#attributes']['src'], array('attributes' => array('rel' => 'lightvideo[][Language: ' . $language. ' - Name: ' . $name . ']')));
            }
            */
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

