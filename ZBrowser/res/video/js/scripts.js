jQuery.fn.center = function(parent) {
    if (parent) {
        parent = this.parent();
    } else {
        parent = window;
    }
    this.css({
        "position": "absolute",
        "top": ((($(parent).height() - this.outerHeight()) / 2) + $(parent).scrollTop() + "px"),
        "left": ((($(parent).width() - this.outerWidth()) / 2) + $(parent).scrollLeft() + "px")
    });
	return this;
}
jQuery(document).ready(function () {
	$( window ).resize(function() {
		responsiveBGVideo();
	});
	function responsiveBGVideo() {
		if(window.screen.height > window.screen.width || window.screen.height > ((window.screen.width)/1.78)) {
			$("#bgvideowrap").height((window.screen.height+200));
			$("#bgvideowrap").width((window.screen.height+200) * 1.78);
			$("#bgvideowrap").center();
		} else {
			$("#bgvideowrap").width((window.screen.width));
			$("#bgvideowrap").height((window.screen.width)/1.78);
			$("#bgvideowrap").center();
		}
	}
	$( window ).resize();
});
