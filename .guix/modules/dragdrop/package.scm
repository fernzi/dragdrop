;;; Copyright © 2024-2026 Fern Zapata
;;; This file is under the terms of the GNU GPL version 3, or (at your
;;; option) any later version. If you didn't receive a copy of the GPL
;;; along with this file, see <https://www.gnu.org/licenses/>. */

(define-module (dragdrop package)
  #:use-module (guix)
  #:use-module (guix git-download)
  #:use-module (guix build-system cmake)
  #:use-module ((guix licenses) #:prefix license:)
  #:use-module (gnu packages build-tools)
  #:use-module (gnu packages qt))

(define vcs-file?
  (or (git-predicate
       (string-append (current-source-directory) "/../../.."))
      (const #t)))

(define-public dragdrop
  (package
    (name "dragdrop")
    (version "9999-git")
    (source
     (local-file
      "../../.." (git-file-name name version)
      #:recursive? #t
      #:select? vcs-file?))
    (build-system cmake-build-system)
    (arguments
     (list #:configure-flags #~(list "-GNinja")
           #:tests? #f))
    (inputs
     (list qtbase))
    (native-inputs
     (list ninja))
    (synopsis "File drag-and-drop source")
    (description
     "The dragdrop utility acts as a source or sink for
dragging and dropping files into programs running in a terminal
emulator.")
    (home-page "https://github.com/fernzi/dragdrop")
    (license license:gpl3+)))

dragdrop
