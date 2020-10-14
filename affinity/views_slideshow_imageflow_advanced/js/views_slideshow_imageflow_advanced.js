
/**
 *  @file
 *  Initiate all ImageFlow plugins.
 */


(function ($) {
  var viewsSlideshowImageFlowPlayers = new Array();

  Drupal.behaviors.viewsSlideshowImageFlow = {
    attach: function (context) {
      $('.views-slideshow-imageflow-advanced-images:not(.viewsSlideshowImageFlow-processed)', context).addClass('viewsSlideshowImageFlow-processed').each(function () {
        var imageflow = new ImageFlow();
        var id = $(this).attr('id');
        
        var options = Drupal.settings.viewsSlideshowImageFlow[id];

        // We are reusing options object and will pass it to plugin.
        // therefore, we need to do some housekeeping before proceeding.

        // Plugin ID
        options['ImageFlowID'] = id;

        if (!options['reflections']) {
          options['reflections'] = false;
          options['reflectionP'] = 0.0;
        }
        options['percentOther'] = 98;
        
        // Container resize, if required
        if (parseFloat(options['container_width']) !== 0){        
          $(this).css('width',options['container_width']);        
        }

        // Evaluate onClick event
        if (options['onClick']) {
          eval("options['onClick'] = " + options['onClick']);
        }

        imageflow.init(options);        

        // Hide slideshow contorls, if required
        if (!options['show_slideshow_controls']) {
          $(this).find('.slideshow').hide();
        }

        viewsSlideshowImageFlowPlayers[id] = imageflow;
      });
    }
  };

  viewsSlideshowImageFlowPlayer = function (id) {
    return viewsSlideshowImageFlowPlayers[id];
  };
  
  /* VSIA stands for views_slideshow_imageflow_advanced */
  Drupal.behaviors.vsiaVideoDialog = {
    attach: function (context) {
      // Enable video on jQueryUI Dialog
      $('.dialog-opener').once().click(function() {
        var that = this,
            NewDialog = $('<div id="dialog-video" title="' + $(that).attr('title') + '"><div class="mediaelement-video"><video  src="' + $(that).attr('href') + '" width="320" height="240" ></video></div></div>');

        NewDialog.dialog({
          maxWidth: '940',
          modal: true,
          resizable: false,
          width: 'auto',
          open: function(event, ui) {
            Drupal.attachBehaviors(NewDialog);
          },
          beforeClose: function(event, ui) {
            $('video,audio', this).each(function() {
              $(this)[0].player.pause();
            });
          }
        });

        return false;
      });
    }
  };
})(jQuery);
