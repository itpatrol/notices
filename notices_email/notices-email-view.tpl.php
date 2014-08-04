<div class="notice <?php print $zebra; ?><?php if ($notice->new): ?> <?php print " notice-new"; ?><?php endif; ?>" id="notice-<?php print $notice->noticeid; ?>">
    <div class="picture"><img src="/<?php print $picture?>"> </div>
    <div class="date">
      <?php print $time; ?>
    </div>
    <div class="message">
      <?php print $content; ?>
    </div>
    <?php if (isset($links)): ?>
      <?php print $links ?>
    <?php endif ?>
  <div class="clear-both bottom-border"></div>
</div>
