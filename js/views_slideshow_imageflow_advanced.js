
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
      $('.display-in-dialog:not(.video-dialog-processed)').addClass('video-dialog-processed').dialog({
  			autoOpen: false,
  			maxWidth: '940',
  			modal: true,
  			resize: 'auto',
  			width: 'auto'
  		});
  		
  		$('.dialog-opener:not(.video-dialog-processed)').addClass('video-dialog-processed').click(function() {
  		  var vid = $(this).attr('href');
  			$(vid).dialog('open');
  			return false;
  		});
    }
  };
})(jQuery);
