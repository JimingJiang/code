<?php
/**
* Day Sign up plugin
*/
elgg_register_event_handler('init', 'system', 'sign_up_init');
function sign_up_init() {

	elgg_register_page_handler('day_sign_up', 'sign_up_handler');
	elgg_extend_view('css', 'css/site');
	$item = new ElggMenuItem('day_sign_up', '签到', 'day_sign_up/index'); 
	elgg_register_menu_item('site', $item);
	// add sidebar menu items
elgg_register_menu_item('page', array( 'name' => 'rank', 'text' => '排行榜', 'href' => 'day_sign_up/index', 'contexts' => array('day_sign_up'), )); 

	elgg_register_menu_item('page', array( 'name' => 'sign_up', 'text' => '签到', 'href' => 'day_sign_up/sign_up', 'contexts' => array('day_sign_up'), )); 
	elgg_register_menu_item('page', array( 'name' => 'statistics', 'text' => '统计', 'href' => 'day_sign_up/statistics', 'contexts' => array('day_sign_up'), ));

}

function sign_up_handler($page, $identifier) {
	$plugin_path = elgg_get_plugins_path();
	$base_path = $plugin_path.'day_sign_up/pages/day_sign_up'; 
	// select page based on first URL segment after /day_sign_up/
	switch ($page[0]) {
		case 'index':
			require "$base_path/index.php";
			break;
		case 'sign_up':
			require "$base_path/sign_up.php";
			break;
		case 'statistics':
			require "$base_path/statistics.php";
			break;
		default: 
			echo "request for $identifier $page[0]";
			break;
	}
}
