<?php
/**
 * @file
 * The default options available with Views Slideshow: ImageFlow Advanced.
 */

/**
 * @todo: get rid of extra stuff here
 */
function views_slideshow_imageflow_advanced_views_slideshow_slideshow_info() {
  $options = array(
    'views_slideshow_imageflow_advanced' => array(
      'name' => t('ImageFlow'),
      'type' => 'imageflow',
      'accepts' => array(),
      'calls' => array(),
    ),
  );
  return $options;
}

/**
 * Implements hook_views_slideshow_options_form().
 */

function views_slideshow_imageflow_advanced_views_slideshow_slideshow_type_form(&$form, &$form_state, &$view) {
  // Create the form elements for our ImageFlow view options.
  $form['views_slideshow_imageflow_advanced']['container_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Container width'),
    '#size' => 10,
    '#description' => t('Width of ImageFlow container in px, % or em. Set 0 to not apply width to container.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['container_width'],
  );
  $form['views_slideshow_imageflow_advanced']['aspectRatio'] = array(
    '#type' => 'textfield',
    '#title' => t('Aspect ratio'),
    '#size' => 10,
    '#description' => t('Aspect ratio of the ImageFlow container (width divided by height).'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['aspectRatio'],
  );
  $form['views_slideshow_imageflow_advanced']['imagesHeight'] = array(
    '#type' => 'textfield',
    '#title' => t('Images height'),
    '#size' => 10,
    '#description' => t('Height of the images div container to be multiplied.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['imagesHeight'],
  );

  $form['views_slideshow_imageflow_advanced']['slider'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show slider'),
    '#description' => t('Disables / enables the scrollbar.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['slider'],
  );
  $form['views_slideshow_imageflow_advanced']['sliderCursor'] = array(
    '#type' => 'select',
    '#title' => t('Slider cursor'),
    '#description' => t('Cursor type for the slider.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['sliderCursor'],
    '#options' => array(
      'pointer' => t('pointer'),
      'default' => t('default'),
      'e-resize' => t('e-resize'),
    ),
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-slideshow-imageflow-advanced-slider' => array(1)),
  );
  $form['views_slideshow_imageflow_advanced']['scrollbarP'] = array(
    '#type' => 'textfield',
    '#title' => t('Slider width multiplier'),
    '#size' => 10,
    '#description' => t('Width of slider relative to width of container. Values for 0 to 1.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['scrollbarP'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-slideshow-imageflow-advanced-slider' => array(1)),
  );
  $form['views_slideshow_imageflow_advanced']['start'] = array(
    '#type' => 'select',
    '#title' => t('Start position'),
    '#description' => t('The position to begin the ImageFlow.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['start'],
    '#options' => array(
      'start' => t('Start'),
      'middle' => t('Middle'),
      'end' => t('End'),
      'random' => t('Random'),
    ),
  );

  $form['views_slideshow_imageflow_advanced']['min_img_qty'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum images'),
    '#description' => t('How many images to start slideshow.<bt/>If less images then specified value - images will be shown as is, without ImageFlow plugin.<br/>Useful when rotation of 2 items looks odd.<br/>Value must be greater then 0.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['min_img_qty'],
    '#size' => 5,
  );

  $form['views_slideshow_imageflow_advanced']['captions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display captions'),
    '#description' => t('Disables / enables the display of captions.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['captions'],
  );

  // Need to wrap this so it indents correctly.
  $form['views_slideshow_imageflow_advanced']['captions_wrapper'] = array(
    '#markup' => '<div class="vs-dependent">',
  );
  $caption_fields = array();
  foreach ($view->display->handler->get_handlers('field') as $field => $handler) {
    $caption_fields[$field] = $handler->ui_name();
  }
  $form['views_slideshow_imageflow_advanced']['captions_source'] = array(
    '#type' => 'select',
    '#title' => t('Caption source'),
    '#description' => t('Select source field for captions'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['captions_source'],
    '#options' => $caption_fields,
    '#states' => array(
      'visible' => array(
        ':input[name="style_options[views_slideshow_imageflow_advanced][captions]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['views_slideshow_imageflow_advanced']['captions_wrapper_close'] = array(
    '#markup' => '</div>',
  );

  $form['views_slideshow_imageflow_advanced']['imageFocusM'] = array(
    '#type' => 'textfield',
    '#title' => t('Image focus multiplier'),
    '#size' => 10,
    '#description' => t('Multiplier for the focussed image size.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['imageFocusM'],
  );
  $form['views_slideshow_imageflow_advanced']['imageFocusMax'] = array(
    '#type' => 'textfield',
    '#title' => t('Image focus max'),
    '#size' => 10,
    '#description' => t('Maximum number of images on each side of the focussed one.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['imageFocusMax'],
  );
  $form['views_slideshow_imageflow_advanced']['imageCursor'] = array(
    '#type' => 'select',
    '#title' => t('Image cursor'),
    '#description' => t('Cursor type for the images.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['imageCursor'],
    '#options' => array(
      'pointer' => t('pointer'),
      'default' => t('default'),
      'e-resize' => t('e-resize'),
    ),
  );
  $form['views_slideshow_imageflow_advanced']['onClick'] = array(
    '#type' => 'textarea',
    '#title' => t('onClick override'),
    '#description' => t('You may override the onClick JavaScript function of slide show image frames here.'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['onClick'],
  );
  $form['views_slideshow_imageflow_advanced']['slideshowAutoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autoplay'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['slideshowAutoplay'],
    '#description' => t('Toggle automatic slideshow play on startup.'),
  );
    // Need to wrap this so it indents correctly.
  $form['views_slideshow_imageflow_advanced']['slideshowAutoplay_wrapper'] = array(
    '#markup' => '<div class="vs-dependent">',
  );
  $form['views_slideshow_imageflow_advanced']['slideshowSpeed'] = array(
    '#type' => 'textfield',
    '#title' => t('Slideshow speed'),
    '#size' => 10,
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['slideshowSpeed'],
    '#description' => t('Time in miliseconds between rotations.'),
    '#states' => array(
      'visible' => array(
        ':input[name="style_options[views_slideshow_imageflow_advanced][slideshowAutoplay]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['views_slideshow_imageflow_advanced']['show_slideshow_controls'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show slideshow controls'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['show_slideshow_controls'],
    '#description' => t('Toggle slideshow Play/Pause button.'),
    '#states' => array(
      'visible' => array(
        ':input[name="style_options[views_slideshow_imageflow_advanced][slideshowAutoplay]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['views_slideshow_imageflow_advanced']['slideshowAutoplay_wrapper_close'] = array(
    '#markup' => '</div>',
  );

  $form['views_slideshow_imageflow_advanced']['circular'] = array(
    '#type' => 'checkbox',
    '#title' => t('Circular'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['circular'],
    '#description' => t('Toggle circular rotation.'),
  );
  $form['views_slideshow_imageflow_advanced']['startAnimation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Start with animation'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['startAnimation'],
    '#description' => t('Animate images to start position after images loaded.If disabled, images will simply appear once loaded.'),
  );
  $form['views_slideshow_imageflow_advanced']['reflections'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reflections'),
    '#default_value' => $view->options['views_slideshow_imageflow_advanced']['reflections'],
    '#description' => t('Use reflect3.php script shipped with this module to create reflected images. Alternatively, ImageApi with effects can be used to create images with reflection.'),
  );
}

/**
 * Implements hook_views_slideshow_option_definition().
 */
function views_slideshow_imageflow_advanced_views_slideshow_option_definition() {
  // Set our default options.
  $options['views_slideshow_imageflow_advanced'] = array(
    'default' => array(
      'aspectRatio' => 1.964,
      'captions' => TRUE,
      'circular' => FALSE,
      'container_width' => 0,
      'imageCursor' => 'pointer',
      'imagesHeight' => 0.67,
      'imageFocusM' => 1.0,
      'imageFocusMax' => 4,
      'onClick' => 'function() { document.location = this.url; }',
      'reflections' => FALSE,
      'scrollbarP' => 0.6,
      'show_slideshow_controls' => TRUE,
      'slider' => TRUE,
      'sliderCursor' => 'pointer',
      'slideshowAutoplay' => FALSE,
      'slideshowSpeed' => 1500,
      'start' => 'middle',
      'startAnimation' => FALSE,
      'min_img_qty' => 1,
    ),
  );
  return $options;
}

/**
 * Implements hook_views_slideshow_options_form_validate().
 */
function views_slideshow_imageflow_advanced_views_slideshow_options_form_validate(&$form, &$form_state, &$view) {

  // Validate this plugin only if it is selected in "Slideshow type" dropdown.
  // We need to make sure that all plugins use this check.
  if ($form_state['values']['style_options']['slideshow_type'] == 'views_slideshow_imageflow_advanced') {
    $fs = $form_state['values']['style_options']['views_slideshow_imageflow_advanced'];

    if (!is_numeric($fs['aspectRatio'])) {
      form_error($form['views_slideshow_imageflow_advanced']['aspectRatio'], t('<em>!setting</em> must be a number.', array('!setting' => $form['views_slideshow_imageflow_advanced']['aspectRatio']['#title'])));
    }

    if (!preg_match('/^0$|^[0-9]+(.[0-9]+)?(px|em|%|)$/', $fs['container_width'])) {
      form_error($form['views_slideshow_imageflow_advanced']['container_width'], t('<em>!setting</em> must be 0 or a number with a suffix of px, em or %.', array('!setting' => $form['views_slideshow_imageflow_advanced']['container_width']['#title'])));
    }

    if (!is_numeric($fs['imagesHeight'])) {
      form_error($form['views_slideshow_imageflow_advanced']['imagesHeight'], t('<em>!setting</em> must be a number.', array('!setting' => $form['views_slideshow_imageflow_advanced']['imagesHeight']['#title'])));
    }

    if (!is_numeric($fs['imageFocusM'])) {
      form_error($form['views_slideshow_imageflow_advanced']['imageFocusM'], t('<em>!setting</em> must be a number.', array('!setting' => $form['views_slideshow_imageflow_advanced']['imageFocusM']['#title'])));
    }

    if (!preg_match('/^([0-9])+$/', $fs['imageFocusMax'])) {
      form_error($form['views_slideshow_imageflow_advanced']['imageFocusMax'], t('<em>!setting</em> must be an integer number.', array('!setting' => $form['views_slideshow_imageflow_advanced']['imageFocusMax']['#title'])));
    }

    if (!is_numeric($fs['scrollbarP'])) {
      form_error($form['views_slideshow_imageflow_advanced']['scrollbarP'], t('<em>!setting</em> must be a number.', array('!setting' => $form['views_slideshow_imageflow_advanced']['scrollbarP']['#title'])));
    }

    if (!is_numeric($fs['slideshowSpeed'])) {
      form_error($form['views_slideshow_imageflow_advanced']['slideshowSpeed'], t('<em>!setting</em> must be a number.', array('!setting' => $form['views_slideshow_imageflow_advanced']['slideshowSpeed']['#title'])));
    }

    if (!is_numeric($fs['min_img_qty'])) {
      form_error($form['views_slideshow_imageflow_advanced']['min_img_qty'], t('<em>!setting</em> must be a number.', array('!setting' => $form['views_slideshow_imageflow_advanced']['min_img_qty']['#title'])));
    }
    elseif (intval($fs['min_img_qty']) < 1) {
      form_error($form['views_slideshow_imageflow_advanced']['min_img_qty'], t('<em>!setting</em> must be greater then 0.', array('!setting' => $form['views_slideshow_imageflow_advanced']['min_img_qty']['#title'])));
    }
  }
}
