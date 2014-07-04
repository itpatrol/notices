Drupal.behaviors.notice = function(context) {
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
    $("#notice-" + id).hide();
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
};
