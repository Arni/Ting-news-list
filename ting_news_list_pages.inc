<?php

/*
 *
 * 
 */

function ting_news_list_result_ahah($destination, $search_key) {
    $search_key = substr($search_key, -1);
    $searches = variable_get('ting_news_list_searches', array());
    if ($searches && $searches[$search_key]) {
        $result = cache_get(md5($searches[$search_key]['query']));
        if ($result) {
            echo $result->data;
            exit;
        }
        module_load_include('client.inc', 'ting');
        module_load_include('theme.inc', 'ting');

        $search_query = '(' . $searches[$search_key]['query'] . ')';
        $objects = get_news_objects($search_query, 10, 5);

        $result = theme('ting_news_list_panel_list', $objects);
        //Cache for 24 hours
        cache_set(md5($searches[$search_key]['query']), $result, 'cache', time() + 3600);
        echo $result;
    }
    exit;
}

function get_news_objects($search_query, $number_of_objects, $number_of_tries) {
    $cached_objects = cache_get('ting_news_list:objects' . md5($search_query));
    if ($cached_objects) {
        $objects = $cached_objects->data;
    } else {
        $options = array(
            'enrich' => TRUE,
            'sort' => 'acquisitionDate_descending',
        );
        $objects = array();
        for ($i = 1; $i <= $number_of_tries; $i++) {
            $search_result = ting_do_search($search_query, $i, 20, $options);

            if (sizeof($search_result->collections) > 0) {
                foreach ($search_result->collections as $collection) {
                    foreach ($collection->objects as $object) {
                        if ($object && ($object->additionalInformation->detailUrl || $object->additionalInformation->thumbnailUrl)) {
                            $objects[] = $object;
                            break; // Only one object from each collection
                        }
                    }
                    if (count($objects) >= $number_of_objects) {
                        break 2; //We only need a certain number of objects
                    }
                }
            } else {
                break; //There are no more search results
            }
        }
    }
    $ids = array();
    foreach ($objects as $object) {
        $ids[] = $object->localId;
    }
    if ($ids) {
        $items = ding_provider_invoke('availability', 'items', $ids);
        foreach ($objects as $object) {
            $object->availability = $items[$object->localId];
            if (ting_object_is($object, 'reservable')) {
                $object->reservebutton = l(t('Reserve now'), 'ding/reservation/' . $object->localId, array('attributes' => array('class' => 'reserve-now'), 'query' => 'destination=' . $destination));
            }
        }
    }
    //Cache objects for 24 hours
    cache_set('ting_news_list:objects' . md5($search_query), $objects, 'cache', time() + 86400);
    return $objects;
}

?>
