;;; Copyright © 2024 Fern Zapata
;;; This file is under the terms of the GNU GPL ver. 3.
;;; If a copy of the GNU GPL was not included with this
;;; file, see <https://www.gnu.org/licenses/>.

(define-module (dragdrop package)
  #:use-module (git describe)
  #:use-module (gnu packages golang)
  #:use-module (gnu packages qt)
  #:use-module (guix)
  #:use-module (guix build-system cmake)
  #:use-module (guix git)
  #:use-module (guix git-download)
  #:use-module ((guix licenses) #:prefix license:)
  #:use-module (ice-9 popen)
  #:use-module (ice-9 rdelim))

(define %source-dir
  (dirname (dirname (dirname (current-source-directory)))))

(define vcs-file?
  (or (git-predicate %source-dir)
      (const #t)))

(define %vcs-version
  (false-if-git-not-found
   (with-repository %source-dir repo
     (describe-format (describe-workdir repo)))))

(define-public dragdrop
  (package
    (name "dragdrop")
    (version %vcs-version)
    (source
     (local-file
      %source-dir (git-file-name name version)
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

(define-public dragdrop-qt5
  (package
    (inherit dragdrop)
    (name "dragdrop-qt5")
    (inputs (modify-inputs (package-inputs dragdrop)
              (replace "qtbase" qtbase-5)))))

dragdrop
