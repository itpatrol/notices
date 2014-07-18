/**
 * @file
 * Attaches behaviors for the Notices module.
 */

(function ($) {

/**
 * Implements Drupal.behaviors for the Notices module.
 */
 
Drupal.behaviors.notices  = {
  attach: function (context, settings) {
    $("div.notice-new a.noticeread").bind("click", function() {
      var id = $(this).attr('rel');
      $("#notice-" + id).removeClass('notice-new');
      $("#noticeread-" + id).hide();
      $("#notice-" + id + " div.noticeIcon img.new").hide();
      
      //submit ajax mark read
      $.get('/ajax/notices/notices-mark-as-read/' + id);
      return false;
    });
    $("div.notice a.noticeremove").bind("click", function() {
      var id = $(this).attr('rel');
      $("#notice-" + id).toggle("fast");
      //submit ajax mark removed
      $.ajax({
        url: '/ajax/notices/notices-remove/' + id + '/' + $("#notices").attr('rel'),
        dataType: 'json',      
        type: "get",
        success: function(data) {
          $('#notices').append(data.data); 
        }
      });
      return false;
    });
    $("div.notice").bind("mouseenter", function() {    
      $( this ).find("ul.notice-links").toggle("fast");
    });
    $("div.notice").bind("mouseleave", function() {    
      $( this ).find("ul.notice-links").toggle("fast");
    });
    $("#notices-mark-as-read").bind("click", function() {
      $('div.notice-new').removeClass('notice-new');
      $('a.noticeread').hide();
      //submit ajax mark read
      $.get('/ajax/notices/notices-mark-as-read');
      return false;
    });


  },

};

})(jQuery);