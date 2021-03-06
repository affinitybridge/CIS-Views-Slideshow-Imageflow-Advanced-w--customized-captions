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
        $caption .= '<span class="field-value">' . $record->field_field_species_name_scientific[0]['rendered']['#markup'] . '</span>';
        $caption .= '</div>';
      }

      // Other names
      if (isset($record->field_field_species_name_other[0]) && !empty($record->field_field_species_name_other[0]['rendered']['#markup'])) {
        $caption .= '<div class="species-othername"><span class="field-label">Other Name(s):&nbsp;</span>';
        $o_names = array();
        foreach ($record->field_field_species_name_other as $o_name) {
          $o_names[] = $o_name['rendered']['#markup'];
        }
        $caption .= '<span class="field-value">' . implode(', ', $o_names) . '</span>';
        $caption .= '</div>';
      }

      // Species use
      if (count($record->field_field_cis_species_use)>0) {
        $caption .= '<div class="species-speciesuse"><span class="field-label">Species Use:&nbsp;</span> <span class="field-value">';
        foreach ($record->field_field_cis_species_use as $count => $use) {
          $caption .= $record->field_field_cis_species_use[$count]['rendered']['#markup'] . ", ";
        }
        $caption = substr($caption,0,-2);
        $caption .= '</span></div>';
      }

      // Public notes
      if (isset($record->field_field_cis_species_public_notes [0]) && !empty($record->field_field_cis_species_public_notes [0]['rendered']['#markup'])) {
        $caption .= '<div class="species-notes"><span class="field-label">Notes:&nbsp;</span>';
        $caption .= '<span class="field-value">' . $record->field_field_cis_species_public_notes[0]['rendered']['#markup'] . '</span>';
        $caption .= '</div>';
      }

       // Translation
      foreach ($record->field_field_cis_translation as $index => $trans_parent) {
        $trans_item=$trans_parent['rendered']['entity']['field_collection_item'][$trans_parent['raw']['value']];
        if (isset($trans_item['field_cis_translation_lang'][0]['#title']) AND isset($trans_item['field_cis_translation_name'][0]['#markup'])) {
          $language=$trans_item['field_cis_translation_lang'][0]['#title'];
          $name=$trans_item['field_cis_translation_name'][0]['#markup'];

          $caption .= '<table class="species-translation"><tr>';
          $caption .= '<td class="field-label">' . $language . ':&nbsp</td>';
          $caption .= '<td class="field-value">' . $name;

          //audio file
          if (isset($trans_item['field_ckk_translation_arc_audio'])) {
            $archive = $trans_item ['field_ckk_translation_arc_audio']['#items'][0]['entity'];
            $audio_priv_path = $archive->field_cis_arc_attach_audio[LANGUAGE_NONE][0]['uri'];
            $audiopath = file_create_url($audio_priv_path);
            $caption .= '<div class="species-play">' . cis_species_playbutton($audiopath) . '</div>';
          }

          // video popup
          if (isset($trans_item['field_ckk_translation_arc_video'])) {
            $archive = $trans_item ['field_ckk_translation_arc_video']['#items'][0]['entity'];
            $vid_priv_path = $archive->field_cis_arc_attach_video[LANGUAGE_NONE][0]['uri'];
            $vidpath = file_create_url($vid_priv_path);

            // lightbox solution
            //$caption .= '<td>'.l(t('video'), $vidpath, array('attributes' => array('rel' => 'lightvideo[group][' . $language. ': ' . $name . ']'))) .'</td>';

            // video tag solution
            $vid = 'dialog-nid' . $record->nid . '-vid' . $trans_parent['raw']['value'];

            /* Note: the l() function returns "/#$vid" for the url and I just want "#$vid"

            $link = l(t('video'), '',
                array(
                  'attributes' => array('class' => 'dialog-opener'),
                  'fragment' => $vid
                )
              ) .
            */
            $link = '<a href="' . $vidpath . '" class="dialog-opener" title="' . $language . '">' . t('video') . '</a>';

            /*
            $video_dialog = '<div id="' . $vid . '" class="display-in-dialog" title="' . $language . '">' .
              theme('mediaelement_video',
                array(
                  'attributes' => array('src' => $vidpath, 'width' => "320", 'height' => "240"),
                  'settings' => array(
                    'controls' => 1,
                    'download_link' => 0,
                    'download_text' => t('Download video'),
                    'height' => '240',
                    'width' => '320'
                  )
                )
              ) .
            '</div>';
            */

            $caption .= '<div class="vide-wrapper">' . $link . /*$video_dialog .*/ '</div>';
            // end of: video tag solution

          }
          $caption  .= '</td>';
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

