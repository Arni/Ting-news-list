<div class="news-list-item">
    <a id="news-list-link" href="<?php echo $object->url ?>" title="<?php print check_plain($object->title) ?><?php if (!empty($object->creators_string)) {
    print ': ' . check_plain($object->creators_string);
} ?>">
        <img src="<?php echo ting_covers_collection_url($object, '80_x') ?>" alt=""/>
        <?php if (!empty($object->creators_string)) {
 ?>
            <div class="creator"><?php print check_plain($object->creators_string); ?></div>
<?php } ?>
        <div class="title"><?php print check_plain($object->title); ?></div>
    </a>
    <div class="news-status">
     <?php if ($object->availability):?>
        <span class="available">
            <?php print 'hjemme'; ?> 
        </span>
      <?php else :?>
       <span class="not-available">
            <?php print 'udlånt'; ?> 
        </span>
        <?php endif ?>
        <?php if ($object->reservebutton):?>
           <span class="reserve-button buttons">
               <?php print $object->reservebutton; ?>
           </span>
        <?php endif ?>
    </div>
</div>