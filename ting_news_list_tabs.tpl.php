<div class="ting-news-box"><h3><?php t('News') ?></h3>
<div id="news-list-tabs">
    <ul>
        <?php
        for ($i = 0; $i < count($searches); $i++) {
            print '<li><a href="#tabs-' . $i . '">' . $searches[$i]["title"] . '</a></li>';
        }
        ?>
    </ul>
      <?php
        for ($i = 0; $i < count($searches); $i++) {
      	print '<div id="tabs-' . $i . '" class="news-list-tab"></div>';
        }
      ?>
</div>
</div>