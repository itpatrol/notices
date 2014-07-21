<div class="notice notice-view<?php if ($notice->new): ?> <?php print ' notice-new'; ?> <?php endif; ?>" id="notice-<?php print $notice->noticeid; ?>">
  <div class="date">
    <?php print $timeago; ?>
  </div>
  <div class="picture"><img src="/<?php print $picture?>"> </div>
  <div class="message">
    <?php if ($notice->new): ?>
      <span class="new"><?php print t('new');?></span>
    <?php endif ?>
    <?php print $content; ?>
  </div>
  <?php if (isset($links)): ?>
    <?php print $links ?>
  <?php endif ?>
  <div class="clear-both bottom-border"></div>
</div>
