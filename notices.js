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
      $.get('/ajax/notices/notices-mark-read/' + id);
      return false;
    });
    $("div.notice a.noticeremove").bind("click", function() {
      var id = $(this).attr('rel');
      $("#notice-" + id).toggle("slow");
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
  },

};

})(jQuery);