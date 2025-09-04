# Contributing

All contributions of any kind are welcome, and all contributions are appreciated.

## Before Contributing
Before you contribute, Please ensure your code adheres to the [style guide](STYLE_GUIDE.md). Pull requests that do not follow this style may be requested to be revised before they are merged. The goal is to, like many open source projects, have the code follow a single style so it remains readable once you get used to the code style.

I would also highly recomend reading the [internal documentation](./Docs/internal_index.md) to become familiar with the engine methods and the architecture.

## What to Contribute
A contribution is anything that improves the software. This _can_ be a new feature or bug fix, but it can also be writing documentation, or event something as simple as correcting a spelling mistake (which I make a lot of, myself). If you are new to contributing on repo hosting sites like GitHub, the following is a good place to start:

### Good First Contributions
A good first thing to contribut is anything you fully think you understand and are comfortable doing. To give you some ideas of simple things to do, look for issues, TODOs, and FIXMEs in a field that you are comfortable with, and in said field try to look for smaller, less contextual tasks. You can also look for GitHub issues with the 'good first issue' label.

### Types of TODOs
There are three main types of things to do, these are feature TODOs, issues and FIXMEs, they're mostly the same but have purposes.

#### GitHub Issues & Feature Ideas
These are probably the most common type of TODO, they are tracked on GitHub. Fixing an issue mostly involves the three basic steps of error fixing:
- finding the problem (often clearer with well made issue tickets)
- finding the cause (in the code)
- modifying the code to no longer cause the problem
Remember to properly adjust documentation if needed.

Please do **Not** make API breaking changes once we've passed alpha (at version 1.0.0, anything before is alpha). If you do think a API breaking change is neccesary, please open a dedicated GitHub Issue to descuss it and maybe plan it for a next major version (<ins>#</ins>.0.0).

If ever an issue involves the misunderstanding of usage by a user, please dont adjust the code (as long as the code isnt the main part of the problem), instead change the documentation to properly inform users of how to correctly use the software to avoid the problem.

#### Comment FIXMEs & TODOs

>**TL;DR**
> - `// FIXME: This function has a memory leak and needs to be fixed.` (A known bug that needs to be addressed).
> - `// TODO: Add a proper error handling system for file loading.` (A planned future enhancement).
> - find them by searching for `TODO` or `FIXME` in source and/or header files.

**Comment FIXMEs and TODOs are like diet Issues.** They cetainly do have some small diferences, though there are plenty of people that use the interchangably, though for this repo try to adhere to and assume the following uses:

**FIXMEs** are often small things in code that a programmer knew should be done but didn't do themselves (either because they didnt want to, didnt have the time, or didnt know how), or that someone else saw and realized was something to fix.

**TODOs** though, are the sort of next steps that the programmer things is a good next thing to do, either because they had to push a commit and wanted to come back later or because they thought it was a good idea but not neccecary for the feature to work. For the later, please prefer GitHub Feature Issues over Comment TODOs (which should be used for smaller and more internal details or optimization points).

**To find Comment TODOs and FIXMEs**, I'd recomend to just go through source and header files (starting with the files on topics you like and/or are familiar with) and use a word find/search tool to find `TODO:` or `FIXME:` (which should be the keywords you use when adding a Comment TODO or FIXME), though you might leave out the `':'` to make the search more inclusive.

### Contribution Through Testing
Another good way to contribute is through testing or benchmarking parts of or the entire engine and reporting details to the GitHub, this can be done mostly through Issues, but also by making contributions to the ['Performance'](./README.md#performance) section in `README.md`.

To build for testing, benchmarking or debugging, I'd recomend the following build flags (as a minimum, you could add any aditional non-conflicting flags you'd like):
- use `--debug` or `-d` to compile with debugging symbols, to make finding issues easier
- use `--optimize 0` or `-O0` to not optimize, again, to make finding issues easier
- I would also recomend specifying the target details with the `-s`/`--platform` and `-a`/`--arch` flags, even if its the compiler's system's details. So the compiler can perform target specific optimizations
<!-- and the `-C, --compiler`, `-L, --linker` and `-A, --assembler` flags -->
- if testing a release build use `-r`/`--release`, `-O4`/`--optimize 4`, with `-s`/`--platform` and `-a`/`--arch` instead.

For debugging, the engine doesnt have any real dedicated systems or debuggers yet, do fo now just use your own debugger like `gdb`.

There is a benchmarking [`Example`](./Examples/EXAMPLES.md) in the works ([here](./Examples/BenchMark/)), to use it to benchmark, just compile and run it.

To report an issue, please do so on GitHub. First make sure it isnt already a known issue, then identify the core actual problem, and finaly post an issue on GitHub with as many (relevant) details as possible. Read more [here](./README.md#reporting-issues).

There might also be branches dedicated to new features that are in a testing fase, helping test these can often significantly help the progression of the feature.

## How to Contribute
To make something, use the methods you use best, use what you like, but remember to do one thing:

### How to Show That You are Working on Something
If ever you decide to work on an issue or feature from the GitHub Issues page, please do the following so multiple people wont end up doing the same thing:
- Assign yourself to the issue.
- Add a 'assigned', 'blocked', 'on hold', 'in progress' or 'working on it' label to the issue.
- Add line like `Closes #123`* or `Fixes #123`* to the description of a pull request that closes of fixes a GitHub issue.
- [optional] Comment on the issue, to say something like "Hey there, I'll be working on it!".
- [optional] For major features, you can make a new branch with a name like `fix-bug-#42`* or `feat-new-feature-#123`* (where `bug` and `new-feature` should be replaced by the name of the actual bug or feature, e.g. `fix-vulkan-tearing-#53` for a issue on screen tearing for the vulkan renderer with GitHub Issue ID `53`).

When working on a Comment based TODO or FIXME, though less syncronized (thus, GitHub issues are prefered), try to note that you are working on the TODO or FIXME with a simple note like "\<user\>'s on it", "assigned to \<user\>" or maybe even "assigned to \<user1\> by \<user2\>".

*The number following the hash (`'#'`), should be the GitHub Issue ID.

### Pull Requests
Once you've made a contribution, you would have to submit it to the GitHub repo, to do this you would place a pull-request. When doing so, please be mindful of the following things.

- **Use a clear Title**. Dont just say 'changed some header', instead write something like "Fix: corrected typo in `README.md` in `## usage` under `### platform`, from 'Lunix' to 'Linux'" (though small, has a clear purpose and concise message).
- **In the description tell Why, not just What**. dont just repeate the title with a few extra words, instead add parts like:
    - **What is the problem you are solving** explain the issue and maybe link the GitHub issue again (either through URL, ID or both).
    - **How did you solve it**. explain your method to solving it, and maybe some notes, fixmes and todos that you've added as comments in the code.
    - **Add visuals or examples**. though certainly not required, is very much appreaciated. If your change involves graphical or UI changes.
    - **Add Testing details and results**. If you did test it, which I highly encourage, please do include the details in the pull request description. these would be things like the systems details and platform on which you've had a succesfull test, the benchmarking details (if you have those), and general differences between before the change and after.
- **Give it a specific purpose**. Dont make a bunch of small changes and push those as an ambiguous pull request, instead give it a clear goal (e.g. 'fix issue #' or 'new feature #', with `'#'` being the corresponding GitHub Issue ID, if any).
- **Link the Issue**. If the pull request fixes a GitHub Issue, please do add the ID, this will make my life a whole lot easier.
- **Make sure your change follows the project standards**. make sure you've followed the [code style](./STYLE_GUIDE.md), updated relevant doumentation and have a clean commit history with commits like 'oops forgot X' or 'very small change Y' cleaned up into a more clear and concise commit history (with commands like `git rebase -i`).
- **Double check your pull request before hand**. To make sure it doesnt contain any temporary, testing, build or editor files that you wouldnt want in the repo. Try to check for spelling mistakes and typos to catch them early, so they dont have to become a GitHub Issue.

## Things to Keep in Mind
Beside those 'requirements' there are a few thing you should probably know / keep in mind.

### External Code importing
If ever you decide to use code from other repositories in your commits, there are a few things to keep in mind.
- **Rights and permissions**. Please make sure you have the rights and permissions to use the code. If you do not, or if the license restricts you from viably using the code for this repo, please refrain from doing so. This will reduce the chance of legal trouble and/or licensing conflicts, making it easier for both of us.
- **Integration quality**. Please make sure the code actually works with the repo code, and doesnt conflict with existing code, through symbols, logic, thread safety, etc... if you are not sure, either test it thoroughly (either yourself or by making a new branch for it and having other people help test it), or refrain from using the code.
- **Code formatting**. When using external code, you have two options for formatting:
    - (Prefered) **Adjusting for this repo's [formatting style](./STYLE_GUIDE.md)**. Ideally you would reformat the code to use the formatting style of the repo (e.g. while you are checking or adjusting the code to work with the repo), this should be the default case.
    - **Using the original formatting**. This should only be the case if either the code's license only allows it to be used without modifications (in which case, **Make Sure to Leave a Comment to Let Others Know**), or when the code is very seperated e.g. when adding a full lib or dependency (if you can use the C one, please just use the library, without including its full source, which would significantly bloat the repo).
- **Adding dependencies**. If you decide it would be a good idea to add or remove a dependency library, please make a dedicated issue to discuss it with others before just pushing it in a pull request. If you end up pushing it after having it approved by others, please prefer looking up and linking the lib in CMake instead of including the full source to prevent unnecesary bloat for the repo and so we dont have to update the dependency each time.
- **Stack exchange sites**. When using or planning to use code from Stack overflow or a similar common stack exchange site or community-driven platform, please know that posts, text and code from Stack overflow and likely many others, is by default **Licensed** under `CC BY-SA 4.0`. Since this is a 'copy left'/'share alike' license, please refrain from using it, unless the poster has specified that you can use it under a more permissive license that works with and allows us to keep the MIT License that we are using as of now.

### AI usage
I think AI usage is apsolutely fine, esspecially since this is open source software, but there are a few key points to keep in mind:

#### Reviewing Generated Code
- **Every Time** you use AI to generate code, **Make sure to review it** before blindly using it.

#### AI service EULA, TOS, etc...
If you do use AI to generate code make sure you are aware of and comply with the AI service's EULA (End User License Agreement) and/or TOS (Terms Of Service), if it says you cant use the code in an open source project, **Dont use it**, if it might contain code with a license more restrictive that the MIT one this repo uses, either find out and credit or **Dont use it**.

The Code in this repo is fully open source, and thus **fully open to use in AI training**, if you do not wish for your code to be able to be used for this purpose, refrain from submitting it. And make sure that if you use AI, it's **EULA and/or TOS doesnt restrict usage in the training** of other LLMs/AIs.

#### Code from non open-source software 
When using AI to generate code, be aware of the fact that the AI has a chance of **using code blocks from propriatary code bases** or code bases with a more restricted License. **If this is the case**, treat it like ['Importing External Code'](#external-code-importing).

### Legal Disclaimer
This is not legal advice. since we use a MIT license, _You_ are responsible for your own legal affairs, however we encourage you to ensure your contributions do not create legal issues for the project or its maintainers.

### Misc Details
#### **Community and Communication**
We have two main places to comunicate:
- **The GutHub repo** for more formal issue placement, code contributions and design & decision discussion.
- **The [Discord](https://discord.gg/e6dMFJfGXN)** for more casual, infromal or personal comunication, and morecontextual help or feedback.

#### **Getting Help**
If you get stuck on a bug or have a question about the architecture, never hesitate to ask. You can get support by reaching out on the [Discord](https://discord.gg/e6dMFJfGXN).