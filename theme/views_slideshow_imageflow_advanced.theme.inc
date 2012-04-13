<?php
/**
 * @file
 * Theme and  preprocess functions for the
 * Views Slideshow: ImageFlow Advanced module.
 */

/**
 * We'll grab only the first image from each row.
 */
function template_preprocess_views_slideshow_imageflow_advanced_main_frame(&$vars) {

  $view = $vars['view'];
  $rows = $vars['rows'];
  $options = $vars['settings'];

  // Initialize our $images array.
  $vars['images'] = array();

  // Strip all images from the $rows created by the original view query.
  $rown_num = 0;
  foreach ($rows as $item) {
    preg_match('@(<\s*img\s+[^>]*>)@i', $item, $matches);
    if (isset($matches[1]) && $image = $matches[1]) {
      // We need to add a URL to 'longdesc', as required by the plugin.
      // If our image is in an anchor tag, use its URL.
      preg_match('@<\s*a\s+href\s*=\s*"\s*([^"]+)\s*"[^>]*>[^<]*' . preg_quote($image) . '[^<]*<\s*/a\s*>@i', $item, $urls);


      if (!isset($urls[1]) || !($url = $urls[1])) {
        // Otherwise link to the original image.
        preg_match('@src\s*=\s*"([^"]+)"@i', $image, $urls);
        if (!isset($urls[1]) || !($url = $urls[1])) {
          // If we get this far, there are probably more serious problems.
          // But for now, we'll go to the front page instead.
          $url = url('<front>');
        }
      } 

      // @todo: Get caption from field value and extract plain text.
      // preg_match("/<([^>]+)>([^<]*)</\1>/",
      // $vars['view']->style_plugin->rendered_fields[$k][$nt],
      // $caption_matches);
      // $caption = $caption_matches[1];
      //
      #$caption = $vars['view']->style_plugin->rendered_fields[$row_num][$options['captions_source']]; // affinity customization -- commented this linne, and took out $caption from alt tag below

      // Add the URL to the image's longdesc tag.
      $image = preg_replace('@img\s+@i', 'img alt="" longdesc="' . $url . '" ', $image);
      
      // Add the image to our image array to display.
      $vars['images'][] = $image;
    }
    $rown_num++;
  }

  // There may be a case when rows do not contain images,
  // but contain other data. Because all except images stripped out
  // we may end up with no images. In this case, we have to hide view,
  // otherwise we will have a preloader with 0 images.
  //
  // In case if there are less then min qty of images to start rotation,
  // we are going to render them as is without ImageFlows.
  if (empty($vars['images']) || count($vars['images']) < $options['min_img_qty']) {
    // Clean images array as we are showing items in rows.
    $vars['images'] = array();
    $row_num = 1;
    foreach ($vars['rows'] as $row) {
      $vars['images'][] = theme('views_slideshow_imageflow_advanced_main_frame_row', array('vss_id' => ($vars['vss_id'] . '-' . $row_num), 'items' => $row, 'view' => $vars['view']));
      $row_num++;
    }
    return;
  }

  // Find the path to our plugin.
  $filename_js = views_slideshow_imageflow_advanced_get_file('js');
  $filename_css = views_slideshow_imageflow_advanced_get_file('css');

  if (empty($filename_js) || empty($filename_css)) {
    drupal_set_message(t('Unable to locate ImageFlow plugin.'), 'error');
    return;
  }

  // Add the required JS and CSS.
  drupal_add_js($filename_js);
  drupal_add_css($filename_css);

  // Add our own JS to handle settings.
  drupal_add_js(drupal_get_path('module', 'views_slideshow_imageflow_advanced') . '/js/views_slideshow_imageflow_advanced.js');

  // We are going to process custom values of options here and create
  // new options elements that correspond ImageFlow object properties.
  switch ($options['start']) {
    case 'start':
      $start = 1;
      break;
    case 'end':
      $start = sizeof($rows);
      break;
    case 'middle':
      $start = ceil(sizeof($rows) / 2);
      break;
    case 'random':
      $start = rand(1, sizeof($rows));
      break;
  }
  $options['startID'] = $start;

  // Additional option to start slideshow.
  if ($options['slideshowAutoplay']) {
    $options['slideshow'] = TRUE;
  }

  // Reflect path (if required).
  if ($options['reflections']) {
    $options['reflections'] = TRUE;
    $options['reflectPath'] = $base_url . '/' . drupal_get_path('module', 'views_slideshow_imageflow_advanced') . '/';
    $options['reflectionPNG'] = TRUE;
  }

  if (!$options['captions']) {
    $options['captions'] = FALSE;
  }

  // Add options into page head.
  drupal_add_js(array('viewsSlideshowImageFlow' => array('views-slideshow-imageflow-advanced-images-' . $vars['id'] => $options)), 'setting');
}
