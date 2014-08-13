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
    $("div.notice-new a.notice-mark-read").bind("click", function() {
      var id = $(this).attr('rel');
      $("#notice-" + id).removeClass('notice-new');
      $("#notice-" + id).find("span.new").hide();
      $(this).hide();

      // Submit ajax mark read.
      $.get('/ajax/notices/notices-mark-as-read/' + id);
      return false;
    });
    $("div.notice a.notice-remove").bind("click", function() {
      var id = $(this).attr('rel');
      $("#notice-" + id).toggle("fast");
      // Submit ajax mark removed.
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
    $("#notices-mark-as-read").bind("click", function() {
      $('div.notice-new').find('span.new').hide();
      $('div.notice-new').removeClass('notice-new');
      $('a.notice-mark-read').hide();

      // Submit ajax mark read.
      $.get('/ajax/notices/notices-mark-as-read');
      return false;
    });
  }
};

})(jQuery);
