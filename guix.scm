;; Copyright © 2023 Fern Zapata
;; This program is subject to the terms of the GNU GPL, version 3
;; or, at your option, any later version. If a copy of it was not
;; included with this file, see https://www.gnu.org/licenses/.

(use-modules
 (gnu packages golang)
 (gnu packages qt)
 (guix)
 (guix build-system cmake)
 (guix git-download)
 ((guix licenses) #:prefix license:)
 (ice-9 popen)
 (ice-9 rdelim))

(define vcs-file?
  (or (git-predicate (current-source-directory))
      (const #t)))

(define vcs-version
  (if vcs-file?
      (apply
       git-version
       (string-split
        (string-drop
         (read-line (open-pipe* OPEN_READ "git" "describe" "--long"))
         1) #\-))
      (read-line
       (open-pipe*
        OPEN_READ
        "sed" "-nr" "s/^\\s*VERSION\\s+([0-9](\\.[0-9])*)/\\1/p"
        "CMakeLists.txt"))))

(define-public dragdrop
  (package
    (name "dragdrop")
    (version vcs-version)
    (source
     (local-file
      "." (git-file-name name version)
      #:recursive? #t
      #:select? vcs-file?))
    (build-system cmake-build-system)
    (arguments
     (list #:tests? #f))
    (inputs
     (list qtbase))
    (native-inputs
     (list go-github-com-go-md2man))
    (synopsis "File drag-and-drop source")
    (description
     "The dragdrop utility acts as a source or sink for
dragging and dropping files into programs running in a terminal
emulator.")
    (home-page "https://github.com/fernzi/dragdrop")
    (license license:gpl3+)))

dragdrop
