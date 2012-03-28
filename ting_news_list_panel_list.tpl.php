<?php if ($objects && (sizeof($objects) > 0)) :?>

  <div id="news-list-panel" class="news-list-list">
	  <?php foreach ($objects as $i => $object) : ?>

	      <?php echo theme('ting_news_list_panel_list_entry', $object); ?>

	  <?php endforeach; ?>
  </div>
<?php endif; ?>