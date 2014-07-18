<div class="notice <?php if ($notice->new) { print "notice-new";}?>" id="notice-<?php print $notice->noticeid; ?>">
    <div class="date">
      <?php print $timeago; ?>
    </div>
    <div class="message">
      <?php print $content; ?>
    </div>
    <?php if ( isset($links)) : ?>
       <?php print $links ?>
    <?php endif ?>
  <div class="clear-both bottom-border"></div>
</div>