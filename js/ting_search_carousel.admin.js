
Drupal.behaviors.tingSearchCarouselAdmin = function(context)
{
	Drupal.tingSearchCarouselAdmin.remove();
};

Drupal.tingSearchCarouselAdmin = {};

Drupal.tingSearchCarouselAdmin.remove = function () {
  $('.ting-news-list-search-wrap .remove').click(function () {
    $(this).parents('tr').remove();
    return false;
  });
};
